/*######################################
# University of Information Technology #
# IT007 Operating System               #
# Pham Mai Dung, 19520477              #
# File: page_Replacement_Algorithm.c   #
######################################*/

#include<stdio.h>

int pos_EarliestPage_LRU(int array[], int n)
{
	int i, min = array[0], pos = 0;
	for(i = 1; i < n; ++i)
	{
		if(array[i] < min)
		{
			min = array[i];
			pos = i;
		}
	}
	return pos;
}

int main()
{
    int key;
    int numOfPages, numOfFrames;
    int pageRequests[100], pageFrames[10], queue[10];
    int i, j;
    int faults = 0;
    int avail1, avail2, avail3;
    //choose Default referenced sequence or Manual input sequence
    do 
    {
        printf("\n--- Page Replacement algorithm ---\n1. Default referenced sequence\n2. Manual input sequence\n");
        printf("Enter your selection: ");
        scanf("%d", &key);
        if (key != 1 && key != 2) 
        {
            printf("\nInvalid syntax. Please re-enter!\n");
        }
    } while (key != 1 && key != 2);

    //Default referenced sequence: MSSV + 007. [1, 9, 5, 2, 0, 4, 7, 7, 0, 0, 7]
    if(key == 1)
    {
        numOfPages = 11;
        pageRequests[0] = 1;  
        pageRequests[1] = 9;
        pageRequests[2] = 5;
        pageRequests[3] = 2;
        pageRequests[4] = 0;
        pageRequests[5] = 4;
        pageRequests[6] = 7;      
        pageRequests[7] = 7;
        pageRequests[8] = 0;
        pageRequests[9] = 0;
        pageRequests[10] = 7;
    }

    //Manual input sequence
    if(key == 2)
    {
        printf("\nEnter number of page requests: ");
	    scanf("%d", &numOfPages);	    
        printf("Input the page requests separated by space: \n");
        for (i = 0; i < numOfPages; i++)
        {
            printf("Value No. [%d]:\t", i + 1);
            scanf("%d", &pageRequests[i]);
        }
    }

    //Enter page frames
    printf("\n--- Page Replacement algorithm ---\nEnter page frames: ");
    scanf("%d", &numOfFrames);
	
    //choose the page replacement algorithm
    do 
    {
        printf("\n--- Page Replacement algorithm ---\n1. FIFO algorithm\n2. LRU algorithm\n3. OPT algorithm\n");
        printf("Enter your selection: ");
        scanf("%d", &key);
        if (key != 1 && key != 2 && key != 3) 
        {
            printf("\nInvalid syntax. Please re-enter!\n");
        }
    } while (key != 1 && key != 2 && key != 3);
		
    //FIFO page replacement algorithm
    if (key == 1)
    {
        printf("\n--- Page Replacement algorithm ---\nFIFO algorithm:\n");
        int index;
        for (i = 0; i < numOfFrames; i++)
        {
            pageFrames[i] = -1;
        }
        index = 0;
        printf("\nPages\t|\t\tFrames\t\t\t|\n");
        for (i = 0; i < numOfPages; i++)
        {
            printf("%d\t\t", pageRequests[i]);
            avail1 = 0;
            for(j = 0; j < numOfFrames; j++)
            {
            	if(pageFrames[j] == pageRequests[i])
            	{
            		avail1 = 1;
            	}
            }
            if(avail1 == 0)
            {
		        pageFrames[index] = pageRequests[i];
		        index = (index + 1) % numOfFrames;
		        faults++;
		        for(j = 0; j < numOfFrames; j++)
		        {
		            printf("%d\t", pageFrames[j]);
		        }
		        printf("\t*");
            }
            else 
            {
            	for(j = 0; j < numOfFrames; j++)
		        { 
		            printf("%d\t", pageFrames[j]);
		        }
            }
            printf("\n");
        }
        printf("\nNumber of Page faults : %d\n", faults);
    }
    
    //LRU page replacement algorithm
    if  (key == 2)
    {
    	printf("\n--- Page Replacement algorithm ---\nLRU algorithm:\n");
    	int count = 0, pos;
    	for (i = 0; i < numOfFrames; ++i)
        {
            pageFrames[i] = -1;
        }
        printf("\nPages\t|\t\tFrames\t\t\t|\n");
        for (i = 0; i < numOfPages; i++)
        {
        	avail1 = avail2 = 0;
        	for(j = 0; j < numOfFrames; ++j)
        	{
        		if(pageFrames[j] == pageRequests[i])
        		{
				count++;
				queue[j] = count;
				avail1 = avail2 = 1;
				break;
        		}
        	}
        	if(avail1 == 0)
        	{
        		for(j = 0; j < numOfFrames; ++j)
        		{
        			if(queue[j] == -1)
        			{
        				count++;
        				faults++;
        				pageFrames[j] = pageRequests[i];
					queue[j] = count;
					avail2 = 1;
					break;
        			}
        		}
        	}
        	if(avail2 == 0)
        	{
			    pos = pos_EarliestPage_LRU(queue, numOfFrames);
			    count++;
			    faults++;
			    pageFrames[pos] = pageRequests[i];
			    queue[pos] = count;
        	}
        	printf("\n");
        	printf("%d\t\t", pageRequests[i]);
        	for(j = 0; j < numOfFrames; j++)
		    { 
		        printf("%d\t", pageFrames[j]);
		    }
		    if(avail1 == 0 || avail2 == 0)
		    {
			    printf("\t*");
		    }
        }
        printf("\nNumber of Page faults : %d\n", faults);	
    }
    
    //OPT page replacement algorithm
    if (key == 3)
    {
    	printf("\n--- Page Replacement algorithm ---\nOPT algorithm:\n");
    	int pos, latest, m;
    	for (i = 0; i < numOfFrames; ++i)
        {
            pageFrames[i] = -1;
        }
        printf("\nPages\t|\t\tFrames\t\t\t|\n");
        for (i = 0; i < numOfPages; i++)
        {
        	avail1 = avail2 = 0;
        	for(j = 0; j < numOfFrames; ++j)
        	{
        		if(pageFrames[j] == pageRequests[i])
        		{
				avail1 = avail2 = 1;
				break;
        		}
        	}
        	if(avail1 == 0)
        	{
        		for(j = 0; j < numOfFrames; ++j)
        		{
        			if(pageFrames[j] == -1)
        			{
        				faults++;
        				pageFrames[j] = pageRequests[i];
					avail2 = 1;
					break;
        			}
        		}
        	}
        	if(avail2 == 0)
        	{
			avail3 = 0;
			for(j = 0; j < numOfFrames; ++j)
			{
				queue[j] = -1;
				for(m = i + 1; m < numOfPages; ++m)
				{
					if(pageFrames[j] == pageRequests[m])
					{
						queue[j] = m;
						break;
					}
				}
			}
			for(j = 0; j < numOfFrames; ++j)
			{
				if(queue[j] == -1)
				{
					pos = j;
					avail3 = 1;
					break;
				}
			}
			if(avail3 == 0)
			{
				latest = queue[0];
				pos = 0;
				for(j = 1; j < numOfFrames; ++j)
				{
					if(queue[j] > latest)
					{
						latest = queue[j];
						pos = j;
					}
				}
			}
			pageFrames[pos] = pageRequests[i];
			faults++;
        	}
        	printf("\n");
        	printf("%d\t\t", pageRequests[i]);
        	for(j = 0; j < numOfFrames; j++)
		    { 
		        printf("%d\t", pageFrames[j]);
		    }
		    if(avail1 == 0 || avail2 == 0)
		    {
			    printf("\t*");
		    }
        }
        printf("\nNumber of Page faults : %d\n", faults);
    }
	return 0;
}
