# Database Enhancement
# Create a new document
# Created by Jhon Smith
# Original create code

import json
from bson import json_util
from pymongo import MongoClient

connection = MongoClient('localhost', 27017)
db = connection['city']
collection = db['inspections']

def main():
        myDocument = { "id" : "203022-2020-SMIT","certificate_number":"1212333",
                     "business_name":"Smith Explosives","date":"July 26, 2017","result":"Pass",
                     "sector":"Explosives Retail Dealer - 999","address":{"number":201,"street":"Havant Way",
                     "city":"PERRY","zip":31069},"Comments":"New Business"}
  
        x = collection.insert_one(myDocument)
    
main()