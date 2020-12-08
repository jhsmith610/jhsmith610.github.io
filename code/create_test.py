# Database Enhancement
# Create a new document
# Created by Jhon Smith
# Nov 29, 2020
# CS 499
# Southern New Hampshire University

import json
from bson import json_util
from pymongo import MongoClient

# Establish a variable for the database
connection = MongoClient('localhost', 27017)
db = connection['city']
collection = db['inspections']

def main():
	
	# Asks for the user to input the record to be added.  
	id = input("Enter Inspection to Add: ")
	certNum = input("Enter Certificate Number: ")
	busName = input("Enter Business Name: ")
	inspDate = input("Enter Inspection Date: ")
	result = input("Pass or Fail: ")
	sector = input("Enter Sector: ")

	# Inputs the address number and zip code as integers.
	addressNum = int(input("Enter Address Number: "))
	addressStreet = input("Enter Address Street: ")
	addressCity = input("Enter Address City: ")
	addressZip = int(input("Enter Address Zipcode: "))
	comments = input("Enter Comments: ")
	
	# Combines all of the inputs into 1 record
        myDocument = { "id":id,"certificate_number":certNum,
                     "business_name":busName,"date":inspDate,"result":result,
                     "sector":sector,"address":{"number":addressNum,"street":addressStreet,
                     "city":addressCity,"zip":addressZip},"Comments":comments}
  
        # Adds the record to the database using the insert_one command
	x = collection.insert_one(myDocument)
    
	# Tests to see if the record was added and prints the appropriate output.
        if collection.find_one(myDocument):
          print("Inspection Record Added")
        else:
          print("Something went wrong! Try again!")
  
main()
