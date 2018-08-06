#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct pluto
{
	char id[32];
	char playLED[21];
	char motion[32];
	struct pluto *next;
};
struct pluto *head = NULL;

void insertPluto(char *id, char *playLED, char*motion)
{
	struct pluto *newPluto = (struct pluto *) malloc(sizeof(struct pluto));
	strncpy(newPluto->id, id, sizeof(newPluto->id) -1);
	strncpy(newPluto->playLED, playLED, sizeof(newPluto->playLED) -1);
	strncpy(newPluto->motion, motion, sizeof(newPluto->motion) -1);

	newPluto->next = NULL;
	head = newPluto;
}
void printAllPluto()
{
	struct pluto *currPluto = head;
	while(currPluto != NULL)
	{
		printf("(%s, %s, %s)\n", currPluto->id, currPluto->playLED, currPluto->motion);
		currPluto = currPluto->next;
	}
}

struct pluto *find(char *id)
{
	struct pluto *currPluto = head;
	if(head == NULL)
	{
		printf("no pluto\n");
		return NULL;
	}

	while(strcmp(currPluto->id, id))
	{
		if(currPluto->next == NULL)
		{
			return NULL;
		}
		else
		{
			currPluto = currPluto->next;
		}
	}
	return currPluto;
}
int main(int argc, char const *argv[])
{
	insertPluto("1", "on", "on");
	insertPluto("2", "on", "off");
	insertPluto("3", "off", "on");
	insertPluto("4", "on", "off");
	printAllPluto();
	struct pluto *plutoCurr = find("2");
	printf("find\n");
	if(plutoCurr != NULL)
	{
		printf("(%s, %s, %s)\n",plutoCurr->id, plutoCurr->playLED, plutoCurr->motion);
	}
	else 
	{
		printf("error find\n");
	}
	return 0;
}
