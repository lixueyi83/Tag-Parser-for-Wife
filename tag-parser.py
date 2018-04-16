#!/usr/bin/env python

print ("*********** Parser Process Started *********")

###########################################################################################################
##	Confuration: machine_id, infile, tag_dict
##########################################################################################################
# 
machine_id = "@M"

infile = open("F_3d.fastq")

tag_dict = {
	"tag1": "CTCTTGATGATGAT",
	"tag2": "CTCTTAGTAGTAGT",
	"tag3": "CTCTTTGATGATGA",
	"tag4": "CTCTTGTAGTAGTA",
	"tag5": "CTCTTATGATGATG",
	"tag6": "CTCTTTAGTAGTAG",
	"tag7": "CTCTTCATCATCAT",
	"tag8": "CTCTTACTACTACT",
	"tag9": "CTCTTTCATCATCA",
	"tag10": "CTCTTCTACTACTA",
	"tag11": "CTCTTATCATCATC",
	"tag12": "CTCTTTACTACTAC"
}

###########################################################################################################
##	Creates outfiles 
##########################################################################################################
outfiles = []

def create_output_files():
	## create output files 
	for tag_name in tag_dict.keys():
		outfiles.append(open(tag_name+".fastq", 'w'))

###########################################################################################################
##	parser1: parse file in a loop, funtion looks nicer but consume more runime than the below if-else one
##  	     However, this function can apply to a dynamic varied tag_dict...we jus need to update this tag_dict
##			 Then it will automatically create outfiles as many as tags in the infile.
##########################################################################################################
def run_tags_parser_in_loop():

	create_output_files();
 
	while 1:
	    ## read 4 lines in a loop 
	    line1 = infile.readline()

	    if line1 == '':
	    	break

	    if machine_id in line1:
	        pass
	    else:
	        continue

	    line2 = infile.readline()
	    line3 = infile.readline()
	    line4 = infile.readline()

	    i = 0
	    for key in tag_dict:
	    	if tag_dict[key] in line2:
	    		outfiles[i].write(line1)
	    		outfiles[i].write(line2)
	    		outfiles[i].write(line3)
	    		outfiles[i].write(line4)
	    		i += 1
	    		break
	    else:
	        pass 
	infile.close()
	print ("*********** Parser Process Completed *********")

##############################################################################################################
##	parser2: parse file by using simple if-else check, consume less runtime compared to the one in loop above
##	Note: As long as the tag_dict changes, this function shall be change accordingly.
##############################################################################################################
def run_tags_parser():

	create_output_files();

	while 1:
	    ## read 4 lines in a loop 
	    line1 = infile.readline()
	    
	    ## if reaches end of the file, exit loop
	    if line1 == '':
	        break

	    ## line1 is no empty, check with machineID
	    if machine_id not in line1:
	        continue

	    ## read followin three lines
	    line2 = infile.readline()
	    line3 = infile.readline()
	    line4 = infile.readline()
		
	    if tag_dict["tag1"] in line2:
	        outfiles[0].write(line1)
	        outfiles[0].write(line2)
	        outfiles[0].write(line3)
	        outfiles[0].write(line4)

	    elif tag_dict["tag2"] in line2:
	        outfiles[1].write(line1)
	        outfiles[1].write(line2)
	        outfiles[1].write(line3)
	        outfiles[1].write(line4)

	    elif tag_dict["tag3"] in line2:
	        outfiles[2].write(line1)
	        outfiles[2].write(line2)
	        outfiles[2].write(line3)
	        outfiles[2].write(line4)

	    elif tag_dict["tag4"] in line2:
	        outfiles[3].write(line1)
	        outfiles[3].write(line2)
	        outfiles[3].write(line3)
	        outfiles[3].write(line4)
		
	    elif tag_dict["tag5"] in line2:
	        outfiles[4].write(line1)
	        outfiles[4].write(line2)
	        outfiles[4].write(line3)
	        outfiles[4].write(line4)	
		
	    elif tag_dict["tag6"] in line2:
	        outfiles[5].write(line1)
	        outfiles[5].write(line2)
	        outfiles[5].write(line3)
	        outfiles[5].write(line4)	
		
	    elif tag_dict["tag7"] in line2:
	        outfiles[6].write(line1)
	        outfiles[6].write(line2)
	        outfiles[6].write(line3)
	        outfiles[6].write(line4)
		
	    elif tag_dict["tag8"] in line2:
	        outfiles[7].write(line1)
	        outfiles[7].write(line2)
	        outfiles[7].write(line3)
	        outfiles[7].write(line4)
		
	    elif tag_dict["tag9"] in line2:
	        outfiles[8].write(line1)
	        outfiles[8].write(line2)
	        outfiles[8].write(line3)
	        outfiles[8].write(line4)
		
	    elif tag_dict["tag10"] in line2:
	        outfiles[9].write(line1)
	        outfiles[9].write(line2)
	        outfiles[9].write(line3)
	        outfiles[9].write(line4)
		
	    elif tag_dict["tag11"] in line2:
	        outfiles[10].write(line1)
	        outfiles[10].write(line2)
	        outfiles[10].write(line3)
	        outfiles[10].write(line4)

	    elif tag_dict["tag12"] in line2:
	        outfiles[11].write(line1)
	        outfiles[11].write(line2)
	        outfiles[11].write(line3)
	        outfiles[11].write(line4)

	    else:
	        pass 

	infile.close()
	print ("*********** Parser Process Completed *********")


###########################################################################################################
##	parser1: parse file in a loop, funtion looks nicer but consume more runime than the below if-else one
#########################################################################################################
##run_tags_parser_in_loop()
run_tags_parser()


