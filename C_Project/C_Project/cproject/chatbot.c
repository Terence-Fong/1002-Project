/*
 * ICT1002 (C Language) Group Project, AY19 Trimester 1.
 *
 * This file implements the behaviour of the chatbot. The main entry point to
 * this module is the chatbot_main() function, which identifies the intent
 * using the chatbot_is_*() functions then invokes the matching chatbot_do_*()
 * function to carry out the intent.
 *
 * chatbot_main() and chatbot_do_*() have the same method signature, which
 * works as described here.
 *
 * Input parameters:
 *   inc      - the number of words in the question
 *   inv      - an array of pointers to each word in the question
 *   response - a buffer to receive the response
 *   n        - the size of the response buffer
 *
 * The first word indicates the intent. If the intent is not recognised, the
 * chatbot should respond with "I do not understand [intent]." or similar, and
 * ignore the rest of the input.
 *
 * If the second word may be a part of speech that makes sense for the intent.
 *    - for WHAT, WHERE and WHO, it may be "is" or "are".
 *    - for SAVE, it may be "as" or "to".
 *    - for LOAD, it may be "from".
 * The word is otherwise ignored and may be omitted.
 *
 * The remainder of the input (including the second word, if it is not one of the
 * above) is the entity.
 *
 * The chatbot's answer should be stored in the output buffer, and be no longer
 * than n characters long (you can use snprintf() to do this). The contents of
 * this buffer will be printed by the main loop.
 *
 * The behaviour of the other functions is described individually in a comment
 * immediately before the function declaration.
 *
 * You can rename the chatbot and the user by changing chatbot_botname() and
 * chatbot_username(), respectively. The main loop will print the strings
 * returned by these functions at the start of each line.
 */
 
#include <stdio.h>
#include <string.h>
#include "chat1002.h"
 
 
/*
 * Get the name of the chatbot.
 *
 * Returns: the name of the chatbot as a null-terminated string
 */
const char *chatbot_botname() {

	return "Chatbot";
	
}


/*
 * Get the name of the user.
 *
 * Returns: the name of the user as a null-terminated string
 */
const char *chatbot_username() {

	return "User";
	
}


/*
 * Get a response to user input.
 *
 * See the comment at the top of the file for a description of how this
 * function is used.
 *
 * Returns:
 *   0, if the chatbot should continue chatting
 *   1, if the chatbot should stop (i.e. it detected the EXIT intent)
 */
int chatbot_main(int inc, char *inv[], char *response, int n) {
	
	/* check for empty input */
	if (inc < 1) {
		snprintf(response, n, "");
		return 0;
	}

	/* look for an intent and invoke the corresponding do_* function */
	if (chatbot_is_exit(inv[0]))
		return chatbot_do_exit(inc, inv, response, n);
	else if (chatbot_is_smalltalk(inv[0]))
		return chatbot_do_smalltalk(inc, inv, response, n);
	else if (chatbot_is_load(inv[0]))
		return chatbot_do_load(inc, inv, response, n);
	else if (chatbot_is_question(inv[0]))
		return chatbot_do_question(inc, inv, response, n);
	else if (chatbot_is_reset(inv[0]))
		return chatbot_do_reset(inc, inv, response, n);
	else if (chatbot_is_save(inv[0]))
		return chatbot_do_save(inc, inv, response, n);
	else {
		snprintf(response, n, "I don't understand \"%s\".", inv[0]);
		return 0;
	}

}


/*
 * Determine whether an intent is EXIT.
 *
 * Input:
 *  intent - the intent
 *
 * Returns:
 *  1, if the intent is "exit" or "quit"
 *  0, otherwise
 */
int chatbot_is_exit(const char *intent) {
	
	return compare_token(intent, "exit") == 0 || compare_token(intent, "quit") == 0;
	
}


/*
 * Perform the EXIT intent.
 *
 * See the comment at the top of the file for a description of how this
 * function is used.
 *
 * Returns:
 *   0 (the chatbot always continues chatting after a question)
 */
int chatbot_do_exit(int inc, char *inv[], char *response, int n) {
	 
	snprintf(response, n, "Goodbye!");
	 
	return 1;
	 
}


/*
 * Determine whether an intent is LOAD.
 *
 * Input:
 *  intent - the intent
 *
 * Returns:
 *  1, if the intent is "load"
 *  0, otherwise
 */
int chatbot_is_load(const char *intent) {
	
	/* to be implemented */
	
	return 0;
	
}


/*
 * Load a chatbot's knowledge base from a file.
 *
 * See the comment at the top of the file for a description of how this
 * function is used.
 *
 * Returns:
 *   0 (the chatbot always continues chatting after loading knowledge)
 */
int chatbot_do_load(int inc, char *inv[], char *response, int n) {
	
	/* to be implemented */
	 
	return 0;
	 
}


/*
 * Determine whether an intent is a question.
 *
 * Input:
 *  intent - the intent
 *
 * Returns:
 *  1, if the intent is "what", "where", or "who"
 *  0, otherwise
 */
int chatbot_is_question(const char *intent) {
	
	char* userIntent[] = { "what", "where", "who", "put" };
	/* to be implemented */
	int length = sizeof(userIntent) / sizeof(userIntent[0]);
	for (int i = 0; i < length; i++)
	{
		if (compare_token(intent, userIntent[i])==0)
			return 1;
	}
	
	return 0;
	
}


/*
 * Answer a question.
 *
 * inv[0] contains the the question word.
 * inv[1] may contain "is" or "are"; if so, it is skipped.
 * The remainder of the words form the entity.
 *
 * See the comment at the top of the file for a description of how this
 * function is used.
 *
 * Returns:
 *   0 (the chatbot always continues chatting after a question)
 */
int chatbot_do_question(int inc, char *inv[], char *response, int n) {

	char* currentIntent, *allEntityLower;
	char allEntity[MAX_RESPONSE] = "";
	knowledge_read(fopen(DBFILE, "r"));

	if (compare_token(inv[0], "put") == 0) {
		printf("%s: Please Choose the Intent you wish to insert into (Who, What, Where) - \n", chatbot_botname());
		printf("%s: ", chatbot_username());
		char intentInsert[MAX_INPUT];
		fgets(intentInsert, MAX_INPUT, stdin); 
		strtok(intentInsert, "\n");

		printf("%s: Please Choose the Entity you wish to insert into '%s'- \n", chatbot_botname(), intentInsert);
		printf("%s: ", chatbot_username()); 
		char entityInsert[MAX_INPUT];
		fgets(entityInsert, MAX_INPUT, stdin); 
		strtok(entityInsert, "\n");

		printf("%s: What is the appropriate response for \nIntent: %s \nEntity: %s\n", chatbot_botname(), intentInsert, entityInsert);
		printf("%s: ", chatbot_username());
		char responseInsert[MAX_INPUT];
		fgets(responseInsert, MAX_INPUT, stdin); 
		strtok(responseInsert, "\n");

		printf("%s: Recording-  \nIntent: %s \nEntity: %s \nResponse: %s\n", chatbot_botname(), intentInsert, entityInsert, responseInsert);

		if (knowledge_put(intentInsert, entityInsert, responseInsert) == KB_OK) { 
			snprintf(response, n, "Knowledge has been recorded.");
		}
		else {
			snprintf(response, n, "An error has occured.");
		}

		return 0;
	}


	if (inv[1] == NULL)
	{
		snprintf(response, n, "Please enter a proper input!");
		return 0;
	} 
	
	if(compare_token(inv[1], "is") == 0 || compare_token(inv[1], "are") == 0)
	{
		currentIntent = inv[0];
		strtok(currentIntent, "\n");
		//snprintf(response, n, currentIntent);
		for (int i = 2; i < inc; i++) {
			strcat(allEntity, inv[i]);
			if (inv[i + 1] != NULL) {
				strcat(allEntity, " ");
			}
		}
		strtok(allEntity, "\n");

		knowledge_get(currentIntent, allEntity, response, n);
		if (knowledge_get(inv[0], allEntity, response, n) == KB_NOTFOUND) {
			//if (num == 1) printf("%s: Sorry, I do not know. %s %s?\n", chatbot_botname(), inv[0], entity);
			printf("%s: Sorry, I do not know. %s %s %s?\n", chatbot_botname(), inv[0], inv[1], allEntity);
			printf("%s: ", chatbot_username());
			char input[MAX_INPUT];
			fgets(input, MAX_INPUT, stdin);



			if (strlen(input) == 1) {
				snprintf(response, n, ":-(");
			}
			else {
				if (knowledge_put(inv[0], allEntity, input) == KB_OK) {
					snprintf(response, n, "Thank you.");
				}
				else {
					snprintf(response, n, "An error has occured.");
				}
			}
		}
		return 0;
	}
	else
	{
		return 0;
	}

}


/*
 * Determine whether an intent is RESET.
 *
 * Input:
 *  intent - the intent
 *
 * Returns:
 *  1, if the intent is "reset"
 *  0, otherwise
 */
int chatbot_is_reset(const char *intent) {
	
	/* to be implemented */
	
	return 0;
	
}


/*
 * Reset the chatbot.
 *
 * See the comment at the top of the file for a description of how this
 * function is used.
 *
 * Returns:
 *   0 (the chatbot always continues chatting after beign reset)
 */
int chatbot_do_reset(int inc, char *inv[], char *response, int n) {
	
	/* to be implemented */
	 
	return 0;
	 
}


/*
 * Determine whether an intent is SAVE.
 *
 * Input:
 *  intent - the intent
 *
 * Returns:
 *  1, if the intent is "what", "where", or "who"
 *  0, otherwise
 */
int chatbot_is_save(const char *intent) {
	
	/* to be implemented */
	
	return 0;
	
}


/*
 * Save the chatbot's knowledge to a file.
 *
 * See the comment at the top of the file for a description of how this
 * function is used.
 *
 * Returns:
 *   0 (the chatbot always continues chatting after saving knowledge)
 */
int chatbot_do_save(int inc, char *inv[], char *response, int n) {
	
	/* to be implemented */
	
	return 0;
	 
}
 
 
/*
 * Determine which an intent is smalltalk.
 *
 *
 * Input:
 *  intent - the intent
 *
 * Returns:
 *  1, if the intent is the first word of one of the smalltalk phrases
 *  0, otherwise
 */
int chatbot_is_smalltalk(const char *intent) {
	
	if (intent != "who" && intent != "what" && intent != "when" && intent != "where" && intent != "why" && intent != "how") {
		if (strcmp(intent, "hi") == 0 || strcmp(intent, "hello") == 0 ||
			strcmp(intent, "goodbye") == 0 || strcmp(intent, "good") == 0 ||
			strcmp(intent, "time") == 0) {
			return 1;
		}
		else {

			return 0;
		}
	}

 
}


/*
 * Respond to smalltalk.
 *
 * See the comment at the top of the file for a description of how this
 * function is used.
 *
 * Returns:
 *   0, if the chatbot should continue chatting
 *   1, if the chatbot should stop chatting (e.g. the smalltalk was "goodbye" etc.)
 */
int chatbot_do_smalltalk(int inc, char *inv[], char *response, int n) {
	
	time_t rawtime;
	struct tm* timeinfo;
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	//printf("Current local time and date: %s", asctime(timeinfo));

	//printf("%s", inv[0]);
	//printf("%s", inv[1]); 

	if (strcmp(*inv, "good") == 0) {
		if (strcmp(inv[1], "bye") == 0) {
			snprintf(response, n, "Thank you and Good bye!");
			return 1;
		}
		else if (strcmp(inv[1], "morning") == 0) {
			snprintf(response, n, "Good Morning!");
			return 0;
		}

		else if (strcmp(inv[1], "afternoon") == 0) {
			snprintf(response, n, "Good Afternoon!");
			return 0;
		}

		else if (strcmp(inv[1], "evening") == 0) {
			snprintf(response, n, "Good Evening!");
			return 0;
		}

		else if (strcmp(inv[1], "night") == 0 || strcmp(inv[1], "goodnight") == 0) {
			snprintf(response, n, "Good Night and sleep tight!");
			return 1;
		}
	}

	else if (strcmp(*inv, "time") == 0 || strcmp(*inv, "date") == 0) {
		snprintf(response, n, "The Date and Time is - %s", asctime(timeinfo));
		return 0;
	}

	else
		snprintf(response, n, "Hello! How may I help you?");

	return 0;
	
}
  