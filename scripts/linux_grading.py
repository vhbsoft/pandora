#Python Script To Test banking.cpp
import shutil
import os
import subprocess
import time
import sys

project_directory = "./submissions/"
#Loop Through Student Files
for root, dirnames, filenames in os.walk(project_directory):
	#Get the name of the next directory
	for nextdirectory in dirnames:
		#Copy file from student directory to test directory
		src = project_directory+nextdirectory
		dst = "./testspace/"+nextdirectory
		shutil.copytree(src, dst)

		#Remove Template Code
		original_name = dst+"/banking.cpp"
		template_name = "./template.cpp"
		final_name = "./testspace/final.cpp"
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
		special_lines = 0
		student_id = ""
		student_name = ""

		#Get students name from first line
		first_line = original_file.readline()
		if "//Name:" in first_line:
			student_name = first_line[first_line.find(":")+1:first_line.find("\n")].lstrip()
		else:
			student_name = "Unknown"

		#Get Students SID from second line
		second_line = original_file.readline()
		if "//SID:" in second_line:
			student_id = second_line[second_line.find(":")+1:second_line.find("\n")].lstrip()
		else:
			student_id = "Unknown"

		#Write student code to test file
		final_file.write(first_line)
		final_file.write(second_line)
		for line in original_file.readlines():
			if lines_to_find[special_lines] in line:
				special_lines += 1
				if special_lines == 6:
					final_file.write("== This Is The Updated Template Code\n")
					final_file.write(line)
					stop_printing = True
			if stop_printing:
				break
			else:
				final_file.write(line)
		original_file.close()
		final_file.close()

		#Replace students main with mainold
		sed_cmd = "sed -i \'s/main/mainold/g\' "+final_name
		os.system(sed_cmd)

		#Append Updated Template Code
		#Append Code for Functions from Solutions with altered names
		template_file = open(template_name)
		final_file = open(final_name, 'a')
		for line in template_file.readlines():
			final_file.write(line)
		template_file.close()

		#Loop through different main functions
		main_func_base_name = "Main_Tests/test_"
		main_func_append_name = ["1-3.cpp", "4-6.cpp", "7-9.cpp", "10-13.cpp", "14-17.cpp" ]
		position_of_main_func = final_file.tell()
		final_file.close()
		for i in range(0,5):
			final_file = open(final_name, 'a')
			#Remove Current Main Function
			if(i != 0):
				final_file.seek(position_of_main_func)
				final_file.truncate()
			#Append Next Main Function
			main_func_full_name = main_func_base_name + main_func_append_name[i]
			print main_func_full_name
			next_main_file = open(main_func_full_name)
			for line in next_main_file.readlines():
				final_file.write(line)
			next_main_file.close()
			final_file.close()
			#Compile
			args = ["g++","./testspace/final.cpp","-o","./testspace/final"]
			str_args = [ str(x) for x in args ]
			runExperiment = subprocess.Popen(str_args, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
			(stdout, stderr) = runExperiment.communicate()
			#print stdout
			#print stderr
			#Copy over all test files
			testsrc = "./Decrypted_Test_Files/"
			testdst = "./"
			src_files = os.listdir(testsrc)
			for file_name in src_files:
				encrysrc = testsrc+file_name
				encrydes = testdst+file_name
				shutil.copyfile(encrysrc, encrydes)
			#Run
			#args = ["cd ./testspace;", "./final"]
			#str_args = [ str(x) for x in args ]
			#runExperiment = subprocess.Popen(str_args, stdout=subprocess.PIPE, stderr=subprocess.PIPE)	
			args = ["./testspace/final"]
			str_args = [ str(x) for x in args ]
			runExperiment = subprocess.Popen(str_args, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
			(stdout, stderr) = runExperiment.communicate()
			#print stdout
			#print stderr

			#Store Output

			#Remove Files
			os.system("rm 0c6b2069dba488e2f3d6b659011d0331 5ce438ddbe829820458045524c8ba0b3 5e257b90ced7a89040da578ff3a2e96b 9a90eb41bceb60cea37b0d94b2f72600 8d6f3a59d404519451ebe06ee3329281 9d48ffa482a033f0ece76e5f36e6e337 9dcdb4fb96cc3028d2dc23f8d686586f 134f3ec1b617dab47a7e09acb93d1735 42047eec8d8b328c594123be0dda80eb 92160a250e7e58589ad301cafcaaa989")

		#Print "name \t SID \t score \n " to File
		final_scores = open("./Grading/scores.tsv", 'a')
		student_info = student_name+" \t "+ student_id+ " \t "
		final_scores.write(student_info)
		test_results = open("./test_output")
		#Compare output with expected results
		result_string = ""
		score_count = 0
		for line in test_results:
			#Add Score to Grading Report
			if "Passed" in line:
				result_string = result_string + "1"
				score_count += 1
			else:
				result_string = result_string + "0"
		#Sum the Score from Grading Report
		sum_of_scores = str(score_count)+" \t " + result_string
		final_scores.write(sum_of_scores)
		#Clean Directory #Move Result File
		src_test_output =  "./test_output"
		dst_test_output = "./Grading/"+nextdirectory+".txt"
		shutil.move(src_test_output, dst_test_output)
		os.system("rm -fr ./testspace/*")
		exit()