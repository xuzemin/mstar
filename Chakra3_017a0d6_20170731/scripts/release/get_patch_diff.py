#!/usr/bin/env python
# -*- coding:utf-8 -*-

# Author: bing.zhao

import os ,re ,datetime,string
import shutil
import sys
import csv


def my_rstrip(ss):
	return ss.rstrip('\n')
	
def make_tree(dir_name , num):
	os.chdir(dir_name)
	for i in range(0,num):
		if L[i][0]=="":
			continue 
		if os.path.exists(L[i][0])!=True:
			os.makedirs(L[i][0])
		tmp = os.path.join(root,L[i][0],L[i][1]) # he bin
		if os.path.exists(tmp)==True:
			shutil.copy(tmp,L[i][0])
		else:
			print dir_name
			if dir_name == "old":
				os.remove(os.path.join(L[i][0],L[i][1]))
			else:
				pass
	os.chdir('..')

	

if len(sys.argv) < 4:
	print "Usage: get_commit_diff  COMMIT1 COMMIT2 BRANCH_NAME"
	exit()
else:
	commit_id1 = sys.argv[1]
	commit_id2 = sys.argv[2]
	branch_name = sys.argv[3]

root = os.getcwd()
print root
# 1.store current branch name , commit id 

current_branch_list=os.popen('git branch').read()
current_branch_list=current_branch_list.splitlines()
i=0
while (i<len(current_branch_list)):
	if(current_branch_list[i].find('*')!= -1):
		current_branch = current_branch_list[i]
		break 
	else:
		i=i+1
print current_branch[1:]    # current branch name get 

current_commit=os.popen('git log  --pretty=oneline | head -n 1').read()
current_commit=current_commit.split(' ')
print current_commit[0];    # current commit id get

store_branch=current_branch[1:]
store_commit=current_commit[0]


os.environ['id1']=str(commit_id1)
os.environ['id2']=str(commit_id2)
os.environ['branchname']=str(branch_name)
os.system('git checkout  $branchname ')

if (0== cmp(commit_id1,commit_id2)):
	print "one commit"
	commit_list=commit_id1
else:
	print "one more commit"
	commit_list=os.popen('git log --pretty=oneline $id1...$id2^1').read()

commit_list=commit_list.splitlines()

print "commit count = %d" % len(commit_list)
#print commit_list

#exit()
### reset HEAD ###
#os.system('git reset --hard origin/master')
#os.system('git pull')
i=0
while (i<len(commit_list)):
	print "i = %d" % i
	print "commit=%s" % (commit_list[i])[:7]
	os.environ['id']=str((commit_list[i])[:7])
	os.system('git reset $id --hard')
	output_log=os.popen('git log --date=iso --pretty=format:"%h %cd" | head -n 1').read()
	target_name=output_log.split(' ')

	### get diff file list ###
	L=[]
	fp=os.popen('git diff HEAD HEAD^1 --name-only')
	diff_list=fp.readlines()
	diff_list2=map(my_rstrip,diff_list)
	for file_ in diff_list2:
		#file_ = os.path.join(root,file_)
		print file_
		L.append(os.path.split(file_))
	file_count = len(L)
	#print L

	print os.getcwd()
	### create  new dir
	if os.path.exists("new")!=True:
		os.mkdir("new")
	else:
		os.system('rm new/* -rf')

	make_tree("new",file_count)

	if os.path.exists("old")!=True:
		shutil.copytree("new","old")
	else:
		os.system('rm old -rf')
		shutil.copytree("new","old")

	os.system('git reset HEAD^1  --hard')

	make_tree("old",file_count)
	### move to ./..
	up = os.path.dirname(root)
	print up
	os.chdir(up)                 # switch to ../chakra3

# create  output_floder
	output_floder = "gitdiff_output"
	if os.path.exists(output_floder)!=True:
		os.mkdir(output_floder)

# chdir output_floder and create target_patch_name
	output_floder=os.path.join(up,output_floder)
	os.chdir(output_floder)
	print os.getcwd()
	
	target_patch_name=target_name[1]+'-'+target_name[2]+'-'+target_name[0]
	target_patch_name =  target_patch_name.replace(':','-',3)
	target_patch_name =  target_patch_name.replace('-','',5)

	if os.path.exists(target_patch_name)!=True:
		os.mkdir(target_patch_name)
	else:
		shutil.rmtree(target_patch_name)
		os.mkdir(target_patch_name)
	

	shutil.move(root+'/'+'new',target_patch_name)
	shutil.move(root+'/'+'old',target_patch_name)

	i=i+1
	os.chdir(root)

	print "\33[31m"
	print "output --->:",output_floder+'/'+target_patch_name
	print ""
	print "\33[0m"
#end while

### create csv file and save 
csv_data=os.popen('git log --date=iso --pretty="%cd @ %h @ %s"  $id1...$id2^1').read()
#print csv_data
csv_data=csv_data.splitlines()
#print csv_data

csvfile = file('history.csv', 'wb')
writer = csv.writer(csvfile,dialect='excel')

i=0
writer.writerow(['commit date','commit id','commit message'])
while (i<len(csv_data)):
	#csv_data[i]=csv_data[i].replace(',',' ')
	csv_data[i]=csv_data[i].split('@')
	writer.writerow((csv_data[i])[:])
	i+=1
csvfile.close()

if os.path.exists(output_floder+'/'+'history.csv')!=True: 
	shutil.move('history.csv',output_floder)
else:
	os.remove(output_floder+'/'+'history.csv')
	shutil.move('history.csv',output_floder)

###

# restore branch and commit 
os.environ['s_branch']=str(store_branch)
os.environ['s_commit']=str(store_commit)
os.system('git checkout $s_branch')
os.system('git reset $s_commit --hard')

print "-----------END------------"
