# Code in Python
# Delete a document
# Created by Jhon Smith
# Milestone 1

import json
import pprint
from bson import json_util
from pymongo import MongoClient

connection = MongoClient('localhost', 27017)
db = connection['city']
collection = db['inspections']

def main():
        myDocument = { "id" : "203022-2020-SMIT" }
    
        collection.delete_one(myDocument)
    
        x = collection.find_one(myDocument)
    
        print(x)
  
main()