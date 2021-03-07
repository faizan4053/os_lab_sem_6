void checkOutRr(){
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
					
					inpbuff.push_back(cpu[0]);					
					out.erase(out.begin());
				}
			}
		}
	}


	if(out.size()>0 && out[0].responceTime == -1){
		out[0].responceTime = currTime;
	}

}

void checkInpRr(){
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

void checkCpuRr(){
	if(cpu.size()>0){
		// cout<<"cpu"<<currTime<<endl;
		
		if(cpu[0].responceTime == -1){
			cpu[0].responceTime = currTime;
		}

		cpu[0].oper[0][1]--;

		if(cpu[0].oper[0][1] == 0){
			
			cpu[0].oper.erase(cpu[0].oper.begin());
			
			if(cpu[0].oper.size() == 0){
				
				cpu[0].end = currTime;
				endFiles.push_back(cpu[0]);
				cpu.erase(cpu.begin());

				tempQuant = 0;
			} else {
				if(cpu[0].oper[0][0] == 2){
					inpbuff.push_back(cpu[0]);

					cpu.erase(cpu.begin());
				}else if (cpu[0].oper[0][0] == 3){
					
					outbuff.push_back(cpu[0]);					
					cpu.erase(cpu.begin());
				}
			}
		}
	}else{

		tempQuant = 0;
	}

	if(cpu.size()>0 && cpu[0].responceTime == -1){
		cpu[0].responceTime = currTime;
	}
}


void startExecutionRr(){
	while(!( (processBuffer.size() == 0) &&( out.size() == 0) && (inp.size() == 0) &&( cpu.size() == 0) )){
		printQueue();
		checkCpuRr();
		checkInpRr();
		checkOutRr();
		int i ;
		for(i = 0;i<inpbuff.size();i++){
			inp.push_back(inpbuff[i]);
		}
		inpbuff.clear();

		for(i =0 ;i<outbuff.size();i++){
			out.push_back(outbuff[i]);
		}
		outbuff.clear();

		for(i =0 ;i<cpubuff.size();i++){
			cpu.push_back(cpubuff[i]);
		}
		cpubuff.clear();
		i = 0;
		while(i < processBuffer.size() && currTime >= processBuffer[i].arrivalTime && processBuffer[i].oper.size() > 0 ){
			processBuffer[i].start = currTime;
			if ( processBuffer[i].oper[0][0] == 1){
				if(cpu.size() ==  0 && processBuffer[i].responceTime == -1) processBuffer[i].responceTime = currTime;
				cpu.push_back(processBuffer[i]);
			} else if(processBuffer[i].oper[0][0] == 2) {
				if(inp.size() ==  0 && processBuffer[i].responceTime == -1) processBuffer[i].responceTime = currTime;
				inp.push_back(processBuffer[i]);
			}else if(processBuffer[i].oper[0][0] == 3){
				if(out.size() ==  0 && processBuffer[i].responceTime == -1) processBuffer[i].responceTime = currTime;
				out.push_back(processBuffer[i]);	
			}		
			
			processBuffer.erase(processBuffer.begin());
		}		

		currTime++;
		tempQuant++;
		if(tempQuant == quantVal && cpu.size() > 0 ){
			tempQuant = 0;
			cpu.push_back(cpu[0]);
			cpu.erase(cpu.begin());
			if(cpu[0].responceTime == -1){
				cpu[0].responceTime = currTime;
			}		
		}
	}
}


void RR( vector < struct process > inputProcess){
	processBuffer.assign(inputProcess.begin() ,inputProcess.end());
	
	initnullProc();
	startExecutionRr();
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