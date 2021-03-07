void checkOutLottery (){
	// cout<<"Out"<<endl;
	if(out.size()!=0){
	
		if(out[0].responceTime == -1){
			out[0].responceTime = currTime;
		}


		out[0].oper[0][1]--;

		if(out[0].oper[0][1] == 0){
			
			out[0].oper.erase(out[0].oper.begin());
			
			if(out[0].oper.size() == 0){
				
				out[0].end = currTime;
				endFiles.push_back(out[0]);
				out.erase(out.begin());
			} else {
				if(out[0].oper[0][0] == 1){
					cpubuff.push_back(out[0]);

					out.erase(out.begin());
				}else if (out[0].oper[0][0] == 2){
					
					inpbuff.push_back(out[0]);					
					out.erase(out.begin());
				}
			}
		}
	}
	if(out.size()>0 && out[0].responceTime == -1){
		out[0].responceTime = currTime;
	}	
}
void checkInpLottery(){
	// cout<<"inp"<<endl;
	if(inp.size()!=0){
		// cout<<"inp"<<currTime<<endl;
		
		if(inp[0].responceTime == -1){
			inp[0].responceTime = currTime;
		}



		inp[0].oper[0][1]--;

		if(inp[0].oper[0][1] == 0){
			
			inp[0].oper.erase(inp[0].oper.begin());
			
			if(inp[0].oper.size() == 0){
				
				inp[0].end = currTime;
				endFiles.push_back(inp[0]);
				inp.erase(inp.begin());
			} else {
				if(inp[0].oper[0][0] == 1){
					cpubuff.push_back(inp[0]);

					inp.erase(inp.begin());
				}else if (inp[0].oper[0][0] == 3){
					
					out.push_back(inp[0]);					
					inpbuff.erase(inp.begin());
				}
			}
		}
	}
	if(inp.size()>0 && inp[0].responceTime == -1){
		inp[0].responceTime = currTime;
	}

}


void reschedule(){
	// cout<<"re"<<endl;
	currTicketMax = 0;

	for(int i = 0;i< numOfTickets;i++)
		tickets[i] = -1;

	int totalShare = 0;

	for(int i = 0;i<processBuffer.size();i++){
		totalShare +=processBuffer[i].cpuShare;    
	}

	for(int i = 0;i<processBuffer.size();i++){
		
		processBuffer[i].ticketAssigned = (processBuffer[i].cpuShare * numOfTickets)/totalShare;
		int  j = currTicketMax;
		currTicketMax += processBuffer[i].ticketAssigned;
		while(j<currTicketMax){
			tickets[j] = processBuffer[i].pid;
			j++;
		}
	}
	// printT();
}
void checkCpuLottery(){

	if(processBuffer.size() > 0){
		
		int count = rand() % numOfTickets;
		// cout<<count<<endl;
		// cout<<"Cpu"<<endl;
		count = tickets[count];
		int i = 0;
		while(i < processBuffer.size()&& count != processBuffer[i].pid){
			i++;
		}
		if(i == processBuffer.size()){ return;}
		count = i;
		if(processBuffer[count].responceTime == -1){
			processBuffer[count].responceTime = currTime;
		}

		processBuffer[count].oper[0][1]--;

		if(processBuffer[count].oper[0][1]  == 0){
			processBuffer[count].oper.erase(processBuffer[count].oper.begin());
			if(processBuffer[count].oper.size() == 0 ){
				processBuffer[count].end = currTime;
				endFiles.push_back(processBuffer[count]);
				processBuffer.erase(processBuffer.begin() + count);			
			}else{
				if(processBuffer[count].oper[0][0] == 2){
					inpbuff.push_back(processBuffer[count]);
					processBuffer.erase(processBuffer.begin() + count);	
				}else if(processBuffer[count].oper[0][0] == 3){
					outbuff.push_back(processBuffer[count]);
					processBuffer.erase(processBuffer.begin() + count);	

				}
			}
			reschedule();
		}

	}
}
void startExecutionLottery(){
	reschedule();
	while(!( (processBuffer.size() == 0) &&( out.size() == 0) && (inp.size() == 0)) ){
		// printQueue();
		checkCpuLottery();
		checkInpLottery();
		checkOutLottery();
		int i ;
		for(i = 0;i<inpbuff.size();i++){
			inp.push_back(inpbuff[i]);
		}
		inpbuff.clear();
		
		for(i =0 ;i<outbuff.size();i++){
			out.push_back(outbuff[i]);
		}
		outbuff.clear();

		if(cpubuff.size()>0){
			for(i =0 ;i<cpubuff.size();i++){
				processBuffer.push_back(cpubuff[i]);
			}
			cpubuff.clear();
			reschedule();
		}
		currTime++;
	}

}

void Lottery( vector < struct process > inputProcess){
	processBuffer.assign(inputProcess.begin() ,inputProcess.end());
	
	startExecutionLottery();

	int avgta =0,avgwt =0,avgrt =0,i;
	for( i = 0;i<endFiles.size();i++){
		avgta += endFiles[i].end - endFiles[i].start;
		avgwt += endFiles[i].end - endFiles[i].start - endFiles[i].totalBurst;
		avgrt += endFiles[i].responceTime - endFiles[i].start;
		cout<<"Pid- "<<endFiles[i].pid<<" Turnaround time "<<endFiles[i].end - endFiles[i].start;
		cout<<" Responce Time "<< endFiles[i].responceTime - endFiles[i].start;
		cout<<" Waiting Time "<<endFiles[i].end - endFiles[i].start - endFiles[i].totalBurst <<endl;
	}

	cout<<"Average Turnaround Time = "<<(float)avgta/(float)i<<endl;
	cout<<"Average Responce Time = " <<(float)avgrt/(float)i<<endl;
	cout<<"Average Waiting Time = " <<(float)avgwt/(float)i<<endl;

}