void checkOutMlfq(){
	// cout<<"OUT"<<endl;
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



void checkInpMlfq(){
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

void checkCpuMlfq(){

	// cout<<"cpu"<<endl;
		int i = 0;
		while(i < queues.size() && queues[i].size() == 0) i++;
		
		if(i == queues.size() ) return;
		
		if (queues[i][0].responceTime == -1)
		{
			queues[i][0].responceTime = currTime;
		}
		queues[i][0].oper[0][1]--;
		queues[i][0].currQuant++;
		queues[i][0].currDownT++;
		if(queues[i][0].oper[0][1] == 0){

			queues[i][0].oper.erase(queues[i][0].oper.begin());

			if(queues[i][0].oper.size() == 0){
				queues[i][0].end = currTime;
				endFiles.push_back(queues[i][0]);
				queues[i].erase(queues[i].begin());
			}else {
				if(queues[i][0].currDownT == downT){
					queues[i][0].currPriority = (i==queues.size()-1)? i:i+1 ;
				}
				if(queues[i][0].oper[i][0] == 2){
					inpbuff.push_back(queues[i][0]);
				queues[i].erase(queues[i].begin());					
				}else{
					outbuff.push_back(queues[i][0]);
					queues[i].erase(queues[i].begin());
				}

			}
		}else {
			if(queues[i][0].currDownT == downT){
				queues[i][0].currDownT = 0;
				queues[i][0].currQuant = 0;
				if(i < queues.size()-1){
					queues[i][0].currPriority++;
					queues[i+1].push_back(queues[i][0]);
					queues[i].erase(queues[i].begin());
				}
			} else if(queues[i][0].currQuant == quant[i]){
				queues[i][0].currQuant = 0;
				queues[i].push_back(queues[i][0]);
				queues[i].erase(queues[i].begin());
			}
		}
		i = 0;
		while(i < queues.size() && queues[i].size() == 0) i++;
		if(i!= queues.size() && queues[i][0].responceTime == -1){
			queues[i][0].responceTime = currTime;
		}

}
int checkSize(){
	
	int i = 0;
	
	for (i = 0;i<queues.size();i++){
		if(queues[i].size() > 0){
			return 1;
		}
	}

	return 0 ;
}


void append(vector<struct process> &A, vector<struct process> &B){
	for(int i = 0;i<B.size();i++){
		B[i].currQuant = 0;
		A.push_back(B[i]);
	}
	B.clear();
}
void startExecutionMlfq(){
	while(!( (checkSize() == 0) &&( out.size() == 0) && (inp.size() == 0) &&( processBuffer.size() == 0) )){
		
		// cout<<"main"<<endl;
		checkCpuMlfq();
		checkInpMlfq();
		checkOutMlfq();
				
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
			queues[cpubuff[i].currPriority].push_back(cpubuff[i]);
		}
		cpubuff.clear();
		if(tempUpT + 1 == upT) {
			for( int i = 0;i+1<queues.size();i++){
				append(queues[i],queues[i+1]);
			}
		}
		i = 0;
		while(i < processBuffer.size() && currTime >= processBuffer[i].arrivalTime && processBuffer[i].oper.size() > 0 ){
			processBuffer[i].start = currTime;
			if ( processBuffer[i].oper[0][0] == 1){
				if(queues[0].size() ==  0 && processBuffer[i].responceTime == -1) processBuffer[i].responceTime = currTime;
				processBuffer[i].currQuant = quant[i];
				queues[0].push_back(processBuffer[i]);
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
	}
}
void MLFQ( vector < struct process > inputProcess){
	processBuffer.assign(inputProcess.begin() ,inputProcess.end());
	// cout<<processBuffer.size()<<endl;
	startExecutionMlfq();
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