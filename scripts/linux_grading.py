#Python Script To Test banking.cpp
import shutil
import os
project_directory = "./Projects/"
#Loop Through Student Files
for root, dirnames, filenames in os.walk(project_directory):
	#Get the name of the next directory
	for nextdirectory in dirnames:
		#Copy file from student directory to test directory	    
		src = project_directory+nextdirectory
		dst = "./Testing/"+nextdirectory
		shutil.copytree(src, dst)
		#Remove Template Code
		original_name = dst+"/banking.cpp"
		additional_name = "./Testing/additional.cpp"
		final_name = "./Testing/final.cpp"
		original_file = open(original_name)
		final_file = open(final_name, 'a')
		lines_to_find = [None]*6
		lines_to_find[0] =  "========================================================================================="
		lines_to_find[1] =  "========================================================================================="
		lines_to_find[2] =  "== YOU DO NOT NEED TO UNDERSTAND AND SHOULD NOT CHANGE ANY CODE BELOW THIS LINE"
		lines_to_find[3] =  "========================================================================================="
		lines_to_find[4] =   "========================================================================================="
		lines_to_find[5] =  "*/"
		stop_printing = False
		count_lines = 0
		print nextdirectory
		for line in original_file.readlines():
			if lines_to_find[count_lines] in line:
				print lines_to_find[count_lines]
				count_lines += 1
				if count_lines == 6:
					print "\n Stop Printing reached \n"
					final_file.write(line)
					stop_printing = True
			if stop_printing:
				break
			else:
				final_file.write(line)
		original_file.close()
		final_file.close()
		exit()
		#Append Updated Template Code

		#Append Code for Functions from Solutions with altered names

		#Loop through different main functions

			#Remove Current Main Function

			#Append Next Main Function

			#Compile

			#Run

			#Store Output

			#Compare output with expected results

			#Add Score to Grading Report

		#Sum the Score from Grading Report
		
		#Print "name \t SID \t score \n " to File

		#Clean Directory