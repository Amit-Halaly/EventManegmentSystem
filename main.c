#include <stdio.h>
#include "main.h"

int main() {
	int opt = 0;
	Acountent a;
	EventHallsOwner pOwner;
	EventManager pManager;

	if(!inItManagerAndOwnerAndAcountent(&pManager, &pOwner, &a))
	{
		printf("error init");
		return;
	}

	do {
		printf("Please choose one of the following options\n");
		printf(" 1 - upload system from file (text\\binary)\n");
		printf(" 2 - display system\n");
		printf(" 3 - display subcomponents\n");
		printf(" 4 - add components\n");
		printf(" 5 - sort\n");
		printf(" 6 - find\n");
		printf(" 7 - display profit\n");
		printf(" 8 - print invoice\n");
		printf("-1 - to exit\n");
		scanf("%d", &opt);

		switch (opt)
		{
		case 1:
			uploadSystem(&pManager,&pOwner, &a);
			break;

		case 2:
			displaySystem(&pManager, &pOwner);
			break;

		case 3:
			displaySystemSubcomponents(&pManager, &pOwner);
			break;

		case 4:
			addcomponents(&pManager, &pOwner, &a);
			break;

		case 5:
			eventSort(&pManager);
			break;

		case 6:
			findEvent(&pManager);
			break;

		case 7:
			calcProfit(&a);
			break;

		case 8:
			printInvoiceByDate(&a);
			break;
		}
	} while (opt != -1);
	printf("bye\n");

	if (!saveAllToFiles(&pManager, &pOwner, &a))
		printf("ERROR save program!\n");
	freeEventHallsOwner(&pOwner);
	freeManager(&pManager);
	freeAcountent(&a);
	return 1;

}
int saveAllToFiles(EventManager* pManager, EventHallsOwner* pOwner, Acountent* a)
{
	if (!saveEventManagerFromTxtFile(pManager, EVENTMANAGER_Txt_FILE_NAME))
		return 0;
	if(!saveEventManagerToBinFile(pManager, EVENTMANAGER_BinFILE_NAME, COMPRESSED_WORKER_FILE))
		return 0;
	if(!saveAcounntentToTxtFile(a, ACOUNTENT_Txt_FILE_NAME))
		return 0;
	if(!saveAcounntentToBinFile(a, ACOUNTENT_BinFILE_NAME))
		return 0;
	if (!saveEventHallsOwnerToTxtFile(pOwner, OWNER_Txt_FILE_NAME))
		return 0;
	if(!saveEventHallsOwnerToBinFile(pOwner, OWNER_Bin_FILE_NAME))
		return 0;
	return 1;
}
int inItManagerAndOwnerAndAcountent(EventManager* pManager, EventHallsOwner* pOwner, Acountent* a)
{
	if (!InItManager(pManager))
		return 0;
	if (!InItAcountent(a))
		return 0;
	if (!inItOwner(pOwner))
		return 0;
	return 1;
}
int inItEventManagerAndEventOWnerFromBinFile(EventManager* pManager, EventHallsOwner* pOwner, Acountent* a)
{
	int res = InItEventHallsOwnerFromBinFile(pOwner , OWNER_Bin_FILE_NAME);
	if (!res)
		return 0;
	res = loadAcounntentFromBinFile(a, ACOUNTENT_BinFILE_NAME);
	if (!res)
		return 0;
	res = initEventManagerFromBinFile(pManager, EVENTMANAGER_BinFILE_NAME, COMPRESSED_WORKER_FILE);
	if (!res)
		return 0;
	return 1;
}
int inItEventManagerAndEventOWnerFromTxtFile(EventManager* pManager, EventHallsOwner* pOwner, Acountent* a)
{
	int res = InItEventHallsOwnerFromTxtFile(pOwner,OWNER_Txt_FILE_NAME);
	if (!res)
		return 0;
	res = loadAcounntentFromTxtFile(a, ACOUNTENT_Txt_FILE_NAME);
	if (!res)
		return 0;
	res = initEventManagerFromTxtFile(pManager, EVENTMANAGER_Txt_FILE_NAME);
	if (!res)
		return 0;
	return 1;
}
void uploadSystem(EventManager* pManager, EventHallsOwner* pOwner, Acountent* a)
{
	int choose;
	printf("1 - binary  2 - text\n");
	scanf("%d", &choose);
	switch (choose)
	{
	case 1:
		if (inItEventManagerAndEventOWnerFromBinFile(pManager, pOwner, a))
			printf("success to load the details\n ");
		break;

	case 2:
		if (inItEventManagerAndEventOWnerFromTxtFile(pManager, pOwner, a))
			printf("success to load the details\n ");
		break;
	default:
		printf("invalid choice\n");
	}
}
void displaySystem(EventManager* pManager, EventHallsOwner* pOwner)
{
	printf("EVENT OWNER\n");
	printEventHallsOwner(pOwner);
	printf("\n-----------------------\n\n");
	printf("EVENT MANAGER\n");
	printEventManager(pManager);
}
void displaySystemSubcomponents(EventManager* pManager, EventHallsOwner* pOwner)
{
	printf("EVENT OWNER\n");
	printEventHallsOwner(pOwner);
	printEventHallsOwnerDetails(pOwner);
	printf("\n-----------------------\n\n");
	printf("EVENT MANAGER\n");
	printAllEventManager(pManager);	
}
void addcomponents(EventManager* pManager, EventHallsOwner* pOwner, Acountent* a)
{
	int op = 0;
	printf("Please choose one of the following options\n");
	printf(" 1 - add event\n");
	printf(" 2 - add worker\n");
	printf(" 3 - add eventhall\n");
	scanf("%d", &op);
	switch (op)
	{
	case 1:
		if(!addEvent(pManager, pOwner,a))
			printf("ERROR ADD EVENT\n");
		break;
	case 2:
		if(!addWorker(pManager))
			printf("ERROR ADD WORKER\n");
		break;
	case 3:
		if(!AddEventHalls(pOwner))
			printf("ERROR ADD EVENTHALL\n");
		break;
	default:
		printf("invalid option\n");
		break;
	}	
}