import json
import cv2 as cv
import os
import sys
import shutil


#mypath="./"
#onlyfiles = [f for f in os.listdir(mypath) if os.path.isfile(os.path.join(mypath, f)) and ".png" in f]
#for f in onlyfiles:
#	m=cv.imread(f,cv.CV_8U)
#	if m is not None:
#		cv.imwrite(f,m)
#print(onlyfiles)


args = sys.argv[1:]
if len(args)<2:
	print("2 argumetn is needed!")
	quit()

mode=args[0]
src=args[1]
#dest=args[2]

#if not os.path.exists(dest):
#	print("creating output folder!")
#	os.mkdir(dest)
dest="./temp";


if mode == 'c':

	print("compressing")
	image_list = [f for f in os.listdir(src) if os.path.isfile(os.path.join(src, f)) and ".png" in f]
	#print(image_list)



	if os.path.exists(dest):
		shutil.rmtree(dest)
	os.mkdir(dest)

	names={}
	i=0
	for im in image_list:
		names[im] =str(i)+".png"
		os.rename(src+"/"+im, src+"/"+str(i)+".png")
		i+=1
	#print(names)
	f = open(dest+"/names.txt", "w")
	f.write(json.dumps(names))
	f.close()
		

	os.system(".\\release\\run.exe c "+src+" "+dest)

	shutil.make_archive(src, 'zip', dest)
	
	os.system("pause")

	for o,idx in names.items():
		os.rename(src+"/"+idx, src+"/"+o)


	shutil.rmtree(dest)


elif mode == 'd':

	if os.path.exists(dest):
		shutil.rmtree(dest)
	os.mkdir(dest)


	shutil.unpack_archive(src,dest, 'zip')

	src=src[:-4]
	#print(src)

	#quit()

	if os.path.exists(src):
		shutil.rmtree(src)
	os.mkdir(src)

	#os.system("pause")

	os.system(".\\release\\run.exe d "+dest+" "+src)


	os.system("pause")


	f = open(dest+"/names.txt", "r")
	names=json.loads(f.read())
	f.close()
	#print(names)
	for o,idx in names.items():
		os.rename(src+"/"+idx, src+"/"+o)

	shutil.rmtree(dest)














