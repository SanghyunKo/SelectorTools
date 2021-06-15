#!/usr/bin/env python
import argparse
import os, sys
import shutil
import time

# get arguments
# it will be add on scripts
parser = argparse.ArgumentParser(description="selectorArgs")
parser.add_argument("-a", default=None, required=True, type=str, help="analyzer name")
parser.add_argument("-s", default=None, required=True, type=str, help="TODO: what is this arg for?")
parser.add_argument("-d", default=None, required=True, type=str, help="path to a sample directory")
parser.add_argument("-o", default=None, required=True, type=str, help="output root file name")
parser.add_argument("--se", default=False, action="store_true", help="use SE_Userhome as base data directory")
parser.add_argument("-u", default=None, required=False, type=str, help="provide user name in case you need to use other user's SE_userhome directory")
parser.add_argument("--input_tier", default="NanoAOD", required=False, type=str, help="input tier")
parser.add_argument("--selectorArgs", default=None, required=False, type=str, nargs="+", help="selector arguments")
parser.add_argument("--force", default=False, action="store_true", help="overwrite base directory")
args = parser.parse_args()

class Submitter:
	def __init__(self):
		self.pwd = os.getcwd()
		self.user = ""
		self.se_home = "/pnfs/knu.ac.kr/data/cms/store/user/"
		if args.se and args.u != None:
			self.user = args.u
		else:
			self.user = os.getlogin()
		self.base_name = args.o.split(".")[0]
		self.make_base_dir()
		self.input_dir = ""
		if args.se:
			self.input_dir += self.se_home + self.user + "/" + args.d
		else:
			self.input_dir = args.d
		temp_samples = os.listdir(self.input_dir)
		self.samples = []
		for sample in temp_samples:
			if ".root" in sample:
				self.samples.append(sample)
		# assume that all the samples in the directory share the sample name with suffix of numbers
		# e.g. output from the crab jobs
		# and there is no other root file in the directory
		temp_names = self.samples[0].split("_")
		self.sample_name = "_".join(temp_names[0:-1])
		self.make_scripts()
	
	def make_base_dir(self):
		self.base_dir = self.pwd + "/condor_base/" + self.base_name
		try:
			if os.listdir(self.base_dir):
				if args.force:
					print("//==== INFO: force option activated, base directory will be overwritten")
					shutil.rmtree(self.base_dir)
				else:
					raise Exception("base directory " + self.base_dir + "exists, use --force option to overwrite")
		except:
			pass
		os.mkdir(self.base_dir)
		os.mkdir(self.base_dir + "/output")
		os.mkdir(self.base_dir + "/error")
		os.mkdir(self.base_dir + "/log")
		os.mkdir(self.base_dir + "/scripts")
		os.mkdir(self.base_dir + "/temp")
		print("//==== INFO: Selector output will be stored in condor_base/" + self.base_name)
	def make_scripts(self):
		# make base folder to store histograms
		# make scripts to submit to condor
		# make selector arguments as str
		selector_args = ""
		if not args.selectorArgs == None:
			for arg in args.selectorArgs:
				selector_args += arg + " "
		condor_jdl = """Universe             = vanilla
Executable           = run.sh
GetEnv               = false

WhenToTransferOutput = On_Exit_Or_Evict
ShouldTransferFiles  = yes 
want_graceful_removal = true
request_memory       = 2000
request_disk         = 2048000
use_x509userproxy = True

# stop jobs from running if they blow up in size or memory
periodic_hold        = (DiskUsage/1024 > 10.0*2000 ||  ImageSize/1024 > RequestMemory*2)

+JobFlavour = "workday"
arguments             = $(Process)
output                = """ + self.base_dir + """/output/job_$(Process).out
error                 = """ + self.base_dir + """/error/job_$(Process).err
log                   = """ + self.base_dir + """/log/job_$(Process).log

queue """ + str(len(self.samples))
		run = """#!/bin/sh
cd """ + self.pwd + """
process=$(($1 + 1))

source /cvmfs/cms.cern.ch/cmsset_default.sh
eval `scramv1 runtime -sh`
export LD_PRELOAD="/usr/lib64/libpdcap.so"

./Utilities/scripts/makeHistFile.py"""
                run += """ -f """ + "dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/" + self.user + "/" + args.d + """/""" + self.sample_name + """_${process}.root"""
                run += """ -a """ + args.a + """ -s """ + args.s + """ --input_tier """ + args.input_tier
		run += """ -o condor_base/""" + self.base_name + "/temp/" + self.base_name + """_${process}.root"""

                if not selector_args == "":
                  run += """ --selectorArgs """ + selector_args
		
		file_condor_jdl = open(self.base_dir + "/scripts/condor.jdl", "w")
		file_condor_jdl.write(condor_jdl)
		file_condor_jdl.close()
		file_run = open(self.base_dir + "/scripts/run.sh", "w")
		file_run.write(run)
		file_run.close()
	def submit(self):
		# voms?
		os.chdir(self.base_dir + "/scripts")
		os.system("condor_submit condor.jdl")
	
	def hadd(self):
		try:
			print("//==== INFO: Waiting for the condor jobs to be finished...")
			while True:
				outputs = os.listdir(self.base_dir + "/temp")
				# if job is finished
				if len(outputs) == len(self.samples):
					os.chdir(self.base_dir + "/temp")
					os.system("hadd ../" + args.o + " *.root")
					os.chdir("..")
					shutil.rmtree(self.base_dir + "/temp")
					print("//==== INFO: Job Finished with " + str(len(outputs)) + " samples analyzed")
					break
				else:
					time.sleep(60)
		except Exception as e:
			print("//==== WARNING: Execption occured!", e)
		

if __name__ == "__main__":
	sub = Submitter()
	sub.submit()
	#sub.hadd()

