#Python Script To Test banking.cpp
import shutil
import os
import subprocess

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
		template_name = "./template.cpp"
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
		temp_stop = False
		special_lines = 0
		print nextdirectory
		for line in original_file.readlines():
			if lines_to_find[special_lines] in line:
				print lines_to_find[special_lines]
				special_lines += 1
				if special_lines == 6:
					print "\n Stop Printing reached \n"
					final_file.write("== This Is The Updated Template Code\n")
					final_file.write(line)
					stop_printing = True
			if stop_printing:
				break
			else:
				final_file.write(line)
		original_file.close()
		final_file.close()
		#sed_cmd = "sed -i s/main/mainold/g "+final_name
		#os.system(sed_cmd)
		#Append Updated Template Code
		#Append Code for Functions from Solutions with altered names
		template_file = open(template_name)
		final_file = open(final_name, 'a')
		for line in template_file.readlines():
			final_file.write(line)
		template_file.close()

		#Loop through different main functions
		main_func_base_name = "Main_Tests/test_"
		main_func_append_name = ["1.cpp", "2.cpp", "3.cpp", "4-7.cpp" ]
		position_of_main_func = final_file.tell()

		for i in range(0,3):
			#Remove Current Main Function
			if(i != 0):
				final_file.seek(position_of_main_func)
				final_file.truncate()
			#Append Next Main Function
			main_func_full_name = main_func_base_name + main_func_append_name[i]
			next_main_file = open(main_func_full_name)
			for line in next_main_file.readlines():
				final_file.write(line)
			#Compile
			compile_cmd = "g++ "+final_name
			os.system(compile_cmd)
			#Run

		exit()
			#Store Output


		#Compare output with expected results

			#Add Score to Grading Report

		#Sum the Score from Grading Report
		
		#Print "name \t SID \t score \n " to File

		#Clean Directory