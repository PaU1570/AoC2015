#include <stdio.h>
#include "strtok_r.h"
#include "InputHdl.h"
#include <stdbool.h>

struct sue
{
	int number;
	int children;
	int cats;
	int samoyeds, pomeranians, akitas, vizslas;
	int goldfish;
	int trees;
	int cars;
	int perfumes;
};

enum sue_value
{
	children,
	cats,
	samoyeds,
	pomeranians,
	akitas,
	vizslas,
	goldfish,
	trees,
	cars,
	perfumes,
	none
};

void init_sues (struct sue*, int);
void get_sue_values (struct sue*, char*);
bool is_match(struct sue, struct sue);
int find_match(struct sue*, struct sue);

int main (const int argc, const char **argv)
{
	char *input = getStrc((char*)argv[1]);
	if (input == NULL)
	{
		printf("Couldn't read file '%s'\n", argv[1]);
		return -1;
	}
	
	struct sue reference_sue;
	reference_sue.number = 0;
	printf("Enter information about the Sue you want to find:\n");
	printf("Children: ");
	scanf("%d",&reference_sue.children);
	printf("Cats: ");
	scanf("%d",&reference_sue.cats);
	printf("Samoyeds: ");
	scanf("%d",&reference_sue.samoyeds);
	printf("Pomeranians: ");
	scanf("%d",&reference_sue.pomeranians);
	printf("Akitas: ");
	scanf("%d",&reference_sue.akitas);
	printf("Vizslas: ");
	scanf("%d",&reference_sue.vizslas);
	printf("Goldfish: ");
	scanf("%d",&reference_sue.goldfish);
	printf("Trees: ");
	scanf("%d",&reference_sue.trees);
	printf("Cars: ");
	scanf("%d",&reference_sue.cars);
	printf("Perfumes: ");
	scanf("%d",&reference_sue.perfumes);
	
	struct sue *sues = malloc(sizeof(struct sue) * 500);
	init_sues(sues, 500);
	get_sue_values(sues, input);
	
	/* for (int i = 0; i < 500; i++)
	{
		printf("Sue %d:\n", sues[i].number);
		printf("\tChildren: %d\n", sues[i].children);
		printf("\tCats: %d\n", sues[i].cats);
		printf("\tSamoyeds: %d\n", sues[i].samoyeds);
		printf("\tPomeranians: %d\n", sues[i].pomeranians);
		printf("\tAkitas: %d\n", sues[i].akitas);
		printf("\Vizslas: %d\n", sues[i].vizslas);
		printf("\tGoldfish: %d\n", sues[i].goldfish);
		printf("\tTrees: %d\n", sues[i].trees);
		printf("\tCars: %d\n", sues[i].cars);
		printf("\tPerfumes: %d\n\n", sues[i].perfumes);
	} */
	int match = find_match(sues, reference_sue);
	if (match == -1)
	{
		printf("Couldn't find a match.\n");
		return 0;
	}
	else
	{
		printf("Found her! It's Sue %d:\n", match);
		printf("\tChildren: %d\n", sues[match - 1].children);
		printf("\tCats: %d\n", sues[match - 1].cats);
		printf("\tSamoyeds: %d\n", sues[match - 1].samoyeds);
		printf("\tPomeranians: %d\n", sues[match - 1].pomeranians);
		printf("\tAkitas: %d\n", sues[match - 1].akitas);
		printf("\tVizslas: %d\n", sues[match - 1].vizslas);
		printf("\tGoldfish: %d\n", sues[match - 1].goldfish);
		printf("\tTrees: %d\n", sues[match - 1].trees);
		printf("\tCars: %d\n", sues[match - 1].cars);
		printf("\tPerfumes: %d\n\n", sues[match - 1].perfumes);
	}
	
	free(sues);
	return 0;
}

void init_sues (struct sue *sues, int n)
{
	for (int i = 0; i < n; i++)
	{
		sues[i].number = i + 1;
		sues[i].children = -1;
		sues[i].cats = -1;
		sues[i].samoyeds = -1;
		sues[i].pomeranians = -1;
		sues[i].akitas = -1;
		sues[i].vizslas = -1;
		sues[i].goldfish = -1;
		sues[i].trees = -1;
		sues[i].cars = -1;
		sues[i].perfumes = -1;
	}
}

void get_sue_values (struct sue *sues, char *input)
{
	char *saveptr;
	char *tmp = malloc(sizeof(char) * 20);
	int sue_count = 0;
	int i = 0;
	enum sue_value type = none;
	while (saveptr != NULL)
	{
		if (i == 0)
		{
			strtok_r(input, " ", &saveptr);
			i++;
		}
		else
		{
			strcpy(tmp, strtok_r(NULL, " ,\n", &saveptr));
			
			if (type == none)
			{
				if (strcmp(tmp, "children:") == 0)
				{
					type = children;
				}
				else if (strcmp(tmp, "cats:") == 0)
				{
					type = cats;
				}
				else if (strcmp(tmp, "samoyeds:") == 0)
				{
					type = samoyeds;
				}
				else if (strcmp(tmp, "pomeranians:") == 0)
				{
					type = pomeranians;
				}
				else if (strcmp(tmp, "akitas:") == 0)
				{
					type = akitas;
				}
				else if (strcmp(tmp, "vizslas:") == 0)
				{
					type = vizslas;
				}
				else if (strcmp(tmp, "goldfish:") == 0)
				{
					type = goldfish;
				}
				else if (strcmp(tmp, "trees:") == 0)
				{
					type = trees;
				}
				else if (strcmp(tmp, "cars:") == 0)
				{
					type = cars;
				}
				else if (strcmp(tmp, "perfumes:") == 0)
				{
					type = perfumes;
				}
			}
			else
			{
				switch (type)
				{
					case children :
						sues[sue_count].children = atoi(tmp);
						type = none;
						break;
					case cats :
						sues[sue_count].cats = atoi(tmp);
						type = none;
						break;
					case samoyeds :
						sues[sue_count].samoyeds = atoi(tmp);
						type = none;
						break;
					case pomeranians :
						sues[sue_count].pomeranians = atoi(tmp);
						type = none;
						break;
					case akitas :
						sues[sue_count].akitas = atoi(tmp);
						type = none;
						break;
					case vizslas :
						sues[sue_count].vizslas = atoi(tmp);
						type = none;
						break;
					case goldfish :
						sues[sue_count].goldfish = atoi(tmp);
						type = none;
						break;
					case trees :
						sues[sue_count].trees = atoi(tmp);
						type = none;
						break;
					case cars :
						sues[sue_count].cars = atoi(tmp);
						type = none;
						break;
					case perfumes :
						sues[sue_count].perfumes = atoi(tmp);
						type = none;
						break;
				}
			}
			if (strcmp(tmp, "Sue") == 0)
			{
				sue_count++;
			}
		}
	}
	free(tmp);
}

bool is_match (struct sue input, struct sue reference)
{
	if (input.children != reference.children && input.children != -1)
	{
		return false;
	}
	if (input.cats <= reference.cats && input.cats != -1)
	{
		return false;
	}
	if (input.samoyeds != reference.samoyeds && input.samoyeds != -1)
	{
		return false;
	}
	if (input.pomeranians >= reference.pomeranians && input.pomeranians	!= -1)
	{
		return false;
	}
	if (input.akitas != reference.akitas && input.akitas != -1)
	{
		return false;
	}
	if (input.vizslas != reference.vizslas && input.vizslas != -1)
	{
		return false;
	}
	if (input.goldfish >= reference.goldfish && input.goldfish != -1)
	{
		return false;
	}
	if (input.trees <= reference.trees && input.trees != -1)
	{
		return false;
	}
	if (input.cars != reference.cars && input.cars != -1)
	{
		return false;
	}
	if (input.perfumes != reference.perfumes && input.perfumes != -1)
	{
		return false;
	}
	
	return true;
}

int find_match (struct sue *sues, struct sue reference)
{
	for (int i = 0; i < 500; i++)
	{
		if (is_match(sues[i], reference))
		{
			return sues[i].number;
		}
	}
	return -1;
}