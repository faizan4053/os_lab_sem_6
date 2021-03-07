bool compareSjf(struct process p1,struct process p2){
	return p1.oper[0][1] < p2.oper[0][1];
}
void checkCurrSjf(int i){
	if(currCpu.pid == -1 && i == 1){
		
		if(cpu.size()>0){
			if(cpu[0].responceTime == -1) cpu[0].responceTime= currTime;
			currCpu = cpu[0];
			cpu.erase(cpu.begin());
		}
	}
	if(currInp.pid == -1 && i ==2){
		
		if(inp.size()>0){
			if(inp[0].responceTime == -1) inp[0].responceTime= currTime;
			currInp = inp[0];

			inp.erase(inp.begin());
		}
	}
	if(currOut.pid == -1 && i ==3){
		
		if(out.size()>0){
			if(out[0].responceTime == -1) out[0].responceTime= currTime;
			currOut = out[0];
			out.erase(out.begin());
		}
	}
}
void insertInQueueSjf(struct process p1){
	
	if(p1.oper.size()>0){
		if( p1.oper[0][0] == 1 ){
			
			cpu.push_back(p1);
			sort(cpu.begin(),cpu.end(),compareSjf);

			
		}else if ( p1.oper[0][0] == 2){
			inp.push_back(p1);
			// sort(inp.begin(),inp.end(),compareSjf);

			
		}else if( p1.oper[0][0] == 3){
			out.push_back(p1);
			// sort(out.begin(),out.end(),compareSjf);
		}

	}
	
	checkCurrSjf(1);

	checkCurrSjf(2);
	checkCurrSjf(3);
	return;

}

void checkOutSjf(){
	// cout<<"2"<<endl;
	if(currOut.pid != -1){
		if(currOut.responceTime == -1){
			currOut.responceTime = currTime;
		}

		currOut.oper[0][1]--;
		if(currOut.oper[0][1]  == 0){
			currOut.oper.erase(currOut.oper.begin());
			
			if( currOut.oper.size() == 0){
				currOut.end = currTime;
				endFiles.push_back(currOut);
				
			} else {
				if(currOut.oper[0][0] == 2){
					inpbuff.push_back(currOut);
				}else if(currOut.oper[0][0] == 1){
					cpubuff.push_back(currOut);
				}
			}
			currOut = nullProc;
			checkCurrSjf(3);
		}
	}	
}
void checkInpSjf(){
	// cout<<"3"<<endl;
	if(currInp.pid != -1){
		if(currInp.responceTime == -1){
			currInp.responceTime = currTime;
		}	
	
		currInp.oper[0][1]--;
		if(currInp.oper[0][1]  == 0){
			currInp.oper.erase(currInp.oper.begin());
				
			if( currInp.oper.size() == 0){
				currInp.end = currTime;
				endFiles.push_back(currInp);
									
			} else {
				if(currInp.oper[0][0] == 1){
					cpubuff.push_back(currInp);
				}else if(currInp.oper[0][0] == 3){
					outbuff.push_back(currInp);
				}
			}
			currInp = nullProc;
			checkCurrSjf(2);
		}
	}
}


void checkCpuSjf(){
	// cout<<"4"<<endl;
	if(currCpu.pid != -1){
		if(currCpu.responceTime == -1){
			currCpu.responceTime = currTime;
		}

		currCpu.oper[0][1]--;

		if(currCpu.oper[0][1]  == 0){

			currCpu.oper.erase(currCpu.oper.begin());

			if( currCpu.oper.size() == 0){
				currCpu.end = currTime;
				endFiles.push_back(currCpu);
				
			} else {
				if(currCpu.oper[0][0] == 2){
					inpbuff.push_back(currCpu);
				}else if(currCpu.oper[0][0] == 3){
					outbuff.push_back(currCpu);
				}
			}
			currCpu = nullProc;
			checkCurrSjf(1);

		}
	}

}

void startExecutionSjf(){
	while(!( (processBuffer.size() == 0) &&( out.size() == 0) && (inp.size() == 0) &&( cpu.size() == 0 ) && currCpu.pid == -1 && currInp.pid == -1 && currOut.pid == -1 )){
		// printQueue();
		checkCpuSjf();
		checkInpSjf();
		checkOutSjf();
		int i =0;

		for(i = 0;i<inpbuff.size();i++){
			insertInQueueSjf(inpbuff[i]);
		}
		inpbuff.clear();

		for(i =0 ;i<outbuff.size();i++){
			insertInQueueSjf(outbuff[i]);
		}
		outbuff.clear();

		for(i =0 ;i<cpubuff.size();i++){
			insertInQueueSjf(cpubuff[i]);
		}
		cpubuff.clear();
		
		i =0;
		while(i < processBuffer.size() && currTime >= processBuffer[i].arrivalTime && processBuffer[i].oper.size() > 0 ){
			processBuffer[i].start = currTime;
			
			insertInQueueSjf(processBuffer[i]);	
					
			processBuffer.erase(processBuffer.begin());
		}

		currTime++;
	}
}


void SJF( vector < struct process > inputProcess){
	processBuffer.assign(inputProcess.begin() ,inputProcess.end());
	
	initnullProc();
	startExecutionSjf();
	// cout<<endFiles.size();
	int avgta =0,avgwt =0,avgrt =0,i;
	for( i = 0;i<endFiles.size();i++){
		avgta += endFiles[i].end - endFiles[i].start;
		avgwt += endFiles[i].end - endFiles[i].start - endFiles[i].totalBurst;
		avgrt += endFiles[i].responceTime - endFiles[i].arrivalTime;
		cout<<"Pid- "<<endFiles[i].pid<<" Turnaround time "<<endFiles[i].end - endFiles[i].start;
		cout<<" Responce Time "<< endFiles[i].responceTime - endFiles[i].arrivalTime;
		cout<<" Waiting Time "<<endFiles[i].end - endFiles[i].start - endFiles[i].totalBurst <<endl;
	}

	cout<<"Average Turnaround Time = "<<(float)avgta/(float)i<<endl;
	cout<<"Average Responce Time = " <<(float)avgrt/(float)i<<endl;
	cout<<"Average Waiting Time = " <<(float)avgwt/(float)i<<endl;

}