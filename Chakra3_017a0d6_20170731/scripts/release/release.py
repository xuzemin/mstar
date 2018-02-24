#!/usr/bin/env python
# -*- coding:utf-8 -*-

import os,re,time,shutil,datetime

root= os.getcwd()
boarddef = root+'/project/boarddef/'
sbootbin = root+'/boot/sboot/bin/'

if root[-7:]!= 'chakra3':
	print "please in dir chakra3 run ./script/release/release.py"
	exit()
else:
	os.system('git reset --hard origin/master')
	os.system('git pull')

print "Which COMMIT ID do you release?"
commit_id = raw_input()
os.environ['commmit_id']=str(commit_id)
os.system('git clean -df')
os.system('make realclean')
os.system('git reset --hard $commit_id')


######### select chip #############
list_allchip =  os.listdir(root+'/chip')
print list_allchip

print "Which CHIP  do you want to release?"
release_chip = raw_input()
while len(release_chip)==0 or release_chip not in list_allchip:
	print "Which CHIP  do you want to release?"
	release_chip = raw_input()
	
####### select board #############
list_allboard = os.listdir(boarddef)
for temp in list_allboard:
	print temp

print "Which BOARD file do  you want to release?"

board_need_save=['BD_Default_define.h','Board.h']
board_num = len(board_need_save)-2
input_temp = "temp"
while len(input_temp)!=0:
	print "board",str(board_num)+':',
	input_temp = raw_input()
	if input_temp  not in list_allboard and len(input_temp)!=0:
		print "Error board name!! please check you spell"
	else:
		board_num+=1
		board_need_save.append(input_temp)
if board_num == 0:
	print "you must chose ONE board at least!"
	exit()

### define function ###
def my_rstrip(s):
	return  s.rstrip('.h')

def my_delete(ss):
	if os.path.isdir(ss):
		shutil.rmtree(ss)
	elif os.path.isfile(ss):
		os.remove(ss)

def remove_other_chip(name,list_allchip):
	for chip_name in list_allchip:
		if name.find(chip_name)!=-1 and name.find(release_chip)==-1 \
			or name.find(chip_name.upper())!=-1 and name.find(release_chip.upper())==-1:   
			print "Removing ",os.path.join(root,name)
			if os.path.isdir(os.path.join(root,name)):
				shutil.rmtree(os.path.join(root, name))  # remove dirs
			elif os.path.isfile(os.path.join(root,name)):
				os.remove(os.path.join(root,name))      #remove files

####  remove other board  ###
for board in list_allboard:
	if board not in board_need_save:
		print "Removing ",os.path.join(boarddef,board)
		os.remove(os.path.join(boarddef,board))
		if os.path.exists(os.path.join(sbootbin+board.rstrip('.h'))):
			print "Removing ",os.path.join(sbootbin+board.rstrip('.h'))
			shutil.rmtree(os.path.join(sbootbin+board.rstrip('.h')))
		else:
			pass

### remove other sboot.bin ###
list_allbootbin = os.listdir(sbootbin)
need_save_boot_bin = map(my_rstrip,board_need_save)		
for boot_bin in list_allbootbin:
	if boot_bin not in need_save_boot_bin:
		print os.path.join(sbootbin+boot_bin)
		my_delete(os.path.join(sbootbin+boot_bin))

### removw other chip ###
walk_obj =  os.walk(root,False)
for root, dirs, files in walk_obj:  
    for name in dirs:
		remove_other_chip(name,list_allchip)
    for name in files:
		remove_other_chip(name,list_allchip)

### remove special need del file ##
special_need_del=['unitest',\
				'createChakra3Workspace.sh',\
				'createChakra3WorkspaceSZ.sh',\
				'syncFileToUtServer.sh',\
				'CHK3_Changelist.txt']
for temp in special_need_del:
	print "Removing ",os.path.join(root,temp)
	my_delete(os.path.join(root,temp))

os.system("find . -name *xls* | xargs rm -rfv")
### tar   ### 
dir_name = os.path.dirname(root)
os.chdir(dir_name)
print "taring ..."
os.system('tar -czf chakra3.tar.gz chakra3 --exclude .git')

### rename ###
now = datetime.datetime.now()
today_str =now.strftime("%Y%m%d") 
output_name = "chakra3_"+today_str+"_"+commit_id+'.tar.gz'
os.rename("chakra3.tar.gz",output_name)

print "\33[31m"
print ">>>>>>output file: ../",output_name
print 
