/*
 * ICT1002 (C Language) Group Project, AY19 Trimester 1.
 *
 * This file implements the chatbot's knowledge base.
 *
 * knowledge_get() retrieves the response to a question.
 * knowledge_put() inserts a new response to a question.
 * knowledge_read() reads the knowledge base from a file.
 * knowledge_reset() erases all of the knowledge.
 * kowledge_write() saves the knowledge base in a file.
 *
 * You may add helper functions as necessary.
 */
 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "chat1002.h"

DB_NUM_OF_ROWS = 0;

/*
 * Get the response to a question.
 *
 * Input:
 *   intent   - the question word
 *   entity   - the entity
 *   response - a buffer to receive the response
 *   n        - the maximum number of characters to write to the response buffer
 *
 * Returns:
 *   KB_OK, if a response was found for the intent and entity (the response is copied to the response buffer)
 *   KB_NOTFOUND, if no response could be found
 *   KB_INVALID, if 'intent' is not a recognised question word
 */
int knowledge_get(const char *intent, const char *entity, char *response, int n) {
	
	/* to be implemented */
	if (!chatbot_is_question(intent)) return KB_INVALID;

	// Finds the response
	int i; knowledge k;
	for (i = 0; i < DB_NUM_OF_ROWS; ++i) {
		k = KNOWLEDGEBASE[i];
		if (compare_token(k.intent, intent) == 0) {
			if (compare_token(k.entity, entity) == 0) {
				strncpy(response, k.response, n);
				return KB_OK;
			}
		}
	}

	//strncpy(response, "Sorry, i don't understand", n);
	return KB_NOTFOUND;
	
}


/*
 * Insert a new response to a question. If a response already exists for the
 * given intent and entity, it will be overwritten. Otherwise, it will be added
 * to the knowledge base.
 *
 * Input:
 *   intent    - the question word
 *   entity    - the entity
 *   response  - the response for this question and entity
 *
 * Returns:
 *   KB_FOUND, if successful
 *   KB_NOMEM, if there was a memory allocation failure
 *   KB_INVALID, if the intent is not a valid question word
 */
int knowledge_put(const char* intent, const char* entity, const char* response) {

	/* to be implemented */
	 // Check if intent valid
	if (!chatbot_is_question(intent))
		return KB_INVALID;

	// Finds the response
	//compare the intent in knowledge base with the user intent 
	//compare the entity in knowledge base with the user entity 
	// both must be valid to return found = 1 
	int i, found = 0; knowledge k;
	//for loop to loop thru the row in database to find a match 
	for (i = 0; i < DB_NUM_OF_ROWS; ++i) {
		k = KNOWLEDGEBASE[i];
		if (strcmp(k.intent, intent)== 0 && strcmp(k.entity, entity) == 0) {
			strcpy(KNOWLEDGEBASE[i].response, response);
			found = 1;
		}
	}
	//if unable to get found = 1 then will ass a new response in knowledge base 
	if (!found) {
		strcpy(KNOWLEDGEBASE[DB_NUM_OF_ROWS].intent, intent);
		strcpy(KNOWLEDGEBASE[DB_NUM_OF_ROWS].entity, entity);
		strcpy(KNOWLEDGEBASE[DB_NUM_OF_ROWS].response, response);
		DB_NUM_OF_ROWS++;
	}

		return KB_OK;  //reply "thankyou" 
	}


/*
 * Read a knowledge base from a file.
 *
 * Input:
 *   f - the file
 *
 * Returns: the number of entity/response pairs successful read from the file
 */
	int knowledge_read(FILE * f) {


		/* to be implemented */
		char intent1[MAX_INTENT];
		char line[MAX_RESPONSE];
		char* line_cut;
		char* entity_response;

		if (f == NULL) {
			return 0;
		}

		while (fgets(line, MAX_RESPONSE, f) != NULL)
		{

			if (strlen(line) == 1)
				continue;

			if (line[0] == '[')
			{
				line_cut = &line[1];
				strtok(line_cut, "\n");
				strtok(line_cut, "]");
				strcpy(intent1, line_cut);
			}
			else {
				strtok(line, "\n");
				entity_response = strtok(line, "=");
				strcpy(KNOWLEDGEBASE[DB_NUM_OF_ROWS].intent, intent1);
				//printf(KNOWLEDGEBASE[DB_NUM_OF_ROWS].intent);
				strcpy(KNOWLEDGEBASE[DB_NUM_OF_ROWS].entity, entity_response);
				//printf(KNOWLEDGEBASE[DB_NUM_OF_ROWS].entity);
				entity_response = strtok(NULL, "=");
				strcpy(KNOWLEDGEBASE[DB_NUM_OF_ROWS].response, entity_response);
				//printf(KNOWLEDGEBASE[DB_NUM_OF_ROWS].response);
				DB_NUM_OF_ROWS++;
			}
		}

		/*for (int i = 0; i < DB_NUM_OF_ROWS; i++)
		{
			printf("%s - %s - %s", KNOWLEDGEBASE[i].intent, KNOWLEDGEBASE[i].entity, KNOWLEDGEBASE[i].response);
		}*/

		return 0;
	}


/*
 * Reset the knowledge base, removing all know entitities from all intents.
 */
	void knowledge_reset() {
	
	/* to be implemented */
	
}


/*
 * Write the knowledge base to a file.
 *
 * Input:
 *   f - the file
 */
	void knowledge_write(FILE * f) {
	
	/* to be implemented */
	
}