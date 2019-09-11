#include <chrono>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MQTTClient.h"
#include "MQTT_Func.h"
#include "sqlite3.h"

#include "enumeration.h"
#include "Lib/resource.h"
#include "Lib/ACP.h"
//#include "MN_AEreg.h"
#include "DMR.h"
#if !defined(WIN32)
#include <unistd.h>
#else
#include <windows.h>
#endif

#if defined(_WRS_KERNEL)
#include <OsWrapper.h>
#endif

std::string buf;

std::string Registration(MQTTClient client)
{
    //Create AE
    //Mendatory resources: Operation, To, From, Request Identifier ,Resource Type, Content 
    //Resource Specific Attributes [M]: App-ID, requestReachability, supportedReleaseVersions
    //                              [0]: PointofAccess, ResourceName
    Request Req;
    AE_ID = "S";                    //Initial registration
    //struct Mendatory m1;
    Req.To = CSE_ID; 
    Req.From = AE_ID;
    Req.Request_Identifier = "m_createAE22";
    Req.Resource_Type = 2;
    Req.Operation = 1;
    lcl = true;
    
    //struct CreateAE CAE;
    CAE.resourceName = CLIENTID;
    CAE.requestReachability = true;
    CAE.App_ID = "C01.com.farm.app01";

    return Create_Req(Req);
}

int main() {

    sqlite3 *db;
    int rc;
    char *zErrMsg = 0;
    char *sql;
    char buf1[200];
    
    const char* data = "Callback function called";
    int ch;
    MQTTClient client;
    MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
    
    rc = sqlite3_open("Middle Node.db", &db);

    if( rc ) {
	    fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
	    return(0);
    }	
    else 	fprintf(stderr, "Opened database successfully\n");
    
    
    CreateTables(db);
    
    //Connect to MQTT Server
    
    MQTTClient_create(&client, ADDRESS, CLIENTID, MQTTCLIENT_PERSISTENCE_NONE, NULL);
    conn_opts.keepAliveInterval = 20;
    conn_opts.cleansession = 1;
    
    MQTTClient_setCallbacks(client, NULL, connlost, msgarrvd, delivered);

    if ((rc = MQTTClient_connect(client, &conn_opts)) != MQTTCLIENT_SUCCESS)
    {
        printf("Failed to connect, return code %d\n", rc);
        //exit(EXIT_FAILURE);
    }
    
    //Create MQTT Subscribe Topic for Initial Registration Request
    //create_Topic("reg_req", "Sensor011", "CSE_01");
    create_Topic("reg_req", "+", "CSE_01");
    
    //Subscribe to the Topic
    printf("Subscribing to topic %s\n for client %s using QoS%d\n", TOPIC, CLIENTID, QOS);
    MQTTClient_subscribe(client, TOPIC, QOS);
    
    ////////////////////////////////Req-Resp Topics//////////////////////////////////////////
    ///char* c_aei;
    ///strcpy(c_aei, RAE.AE_ID.c_str());
    ///Set Topic to /oneM2M/req/SAE01/CSE_01
    //create_Topic("req", "SAE02", "CSE_01");
    create_Topic("req", "+", "CSE_01");
    printf("Subscribing to topic %s\n for client %s using QoS%d\n", TOPIC, CLIENTID, QOS);
    MQTTClient_subscribe(client, TOPIC, QOS);
    
    create_Topic("CSE1234", "Sensor01", "memory001");
    printf("Subscribing to topic %s\n for client %s using QoS%d\n", TOPIC, CLIENTID, QOS);
    MQTTClient_subscribe(client, TOPIC, QOS);
    
    ///TODO: Register CSE in DB//////////////////////////

    //Local AE Registration
    Response Resp;
    buf = Registration(client); 
    process_msg(buf.c_str());
    //check ACP
    if (checkRequestACP(to, From, op, ty))
    {
	cout << "!_!_!_!_!_!_!_!__!_!_!_!_!_!__!_!_!_!" << endl;
	cout << "ACP matched.!" << endl;
    }
    else cout << "ACP not matched.!" << endl;
    if(op == 1&& ty == 2) {
	//Create response code
	
	RES.Resource_Type = ty;
	RES.resourceName = rn;
	///RES.resourceID = ;
	///RES.parentID = ;
	///RES.creationTime = ;          //ct     1
	///RES.lastModifiedTime = ;      //lt     1
	///RES.labels = ;
	RAE.App_ID = api;
	RAE.requestReachability = rr;
	RAE.AE_ID = "SAE01";
	aei = "SAE01"; 
	RAE.pointOfAccess = poa; 
	
	Resp.responseStatusCode = 2001;
	Resp.Request_Identifier = rqi;
	Resp.To = From;
	Resp.From = CSE_ID;
	lcl = true;
	buf = Create_Resp(Resp);
	sleep(2);
	process_msg(buf.c_str());
	//Store in Local DB
	
	sprintf(buf1, "INSERT INTO Registration (aei,api,rn,rr)"\
	" VALUES ('%s', '%s', '%s', '%d');", aei.c_str(), api.c_str(), rn.c_str(), rr); 
	rc = sqlite3_exec(db, buf1, callback, 0, &zErrMsg);
	if( rc != SQLITE_OK ) {
	   fprintf(stderr, "SQL error: %s\n", zErrMsg);
	   sqlite3_free(zErrMsg);
	} 
	else       fprintf(stdout, "Operation done successfully\n");
	op = 0;
	ty = 0;
    }
    char* to1[5];
    char *str_tok;
    int i = 0;
    
    while(1){
        //if(!client->isConnected()) // Check if the client is connected 
        //    break;
        ///Break loop if client is disconnected
	
        if(isMessageArrived){ // Check for the received messages
            sleep(2);
	    process_msg(messageBuffer);
	    //check ACP
            if (checkRequestACP(to, From, op, ty))
            {
                cout << "!_!_!_!_!_!_!_!__!_!_!_!_!_!__!_!_!_!" << endl;
                cout << "ACP matched.!" << endl;
            }
            isMessageArrived = false;
            
	    char* temp1 = new char[to.length() +1];
	    
            RES.Resource_Type = ty;
            ///RES.resourceID = ;
            ///RES.parentID = ;
            ///RES.creationTime = ;          //ct     1
            ///RES.lastModifiedTime = ;      //lt     1
            ///RES.labels = ;
            RES.resourceName = rn;
            Resp.Request_Identifier = rqi;
            Resp.To = From;
            Resp.From = CSE_ID;
            lcl = local;  
	    
	    switch (op){
		case 1:			//CREATE
		    switch(ty){
			case 2:		//AE
			    printf("\n -----------Generating Registration response  -----------\n");
			    //Create response code for CREATE AE
			    RAE.App_ID = api;
			    RAE.requestReachability = rr;
			    RAE.AE_ID = "SAE02"; 			///TODO: CREATE a function to generate AE_ID
			    RAE.pointOfAccess = poa; 
			    
			    //Store in Local DB
			    sprintf(buf1, "INSERT INTO Registration (aei,api,rn,rr)"\
			    " VALUES ('%s', '%s', '%s', '%d');", aei.c_str(), api.c_str(), rn.c_str(), rr); 
			    
			    //Set Topic to /oneM2M/reg_resp/+/CSE_01
			    create_Topic("reg_resp", "Sensor011", "CSE_01");
			break;
			
			case 3:		//CONTAINER
			    printf("\n -----------Generating Container response  -----------\n");
			    //Create response code for CREATE CONTAINER
			    RCnt.stateTag = 0;
			    RCnt.CurrentNrOfInstances = 0;
			    RCnt.CurrentByteSize = 0;
			    
			    //Store in Local DB
			    sprintf(buf1, "INSERT INTO Container (rn, _to, rqi)"\
			    " VALUES ('%s', '%s', '%s');", rn.c_str(), _to, rqi.c_str()); 
			    
			    //Set Topic to /oneM2M/resp/+/CSE_01
			    create_Topic("resp", "SAE02", "CSE_01");
			break;
			
			case 4:		//CONTENTINSTANCE (announceableSubordinateResource)
			    printf("\n -----------Generating CONTENT_INSTANCE response  -----------\n");
			    //Create response code for CREATE CONTENT_INSTANCE
			    //ancsubRES.expirationTime;
			    RCin.contentInfo = cnf;
			    RCin.contentSize = con.length();
			    RCin.content = con;
			    RCin.stateTag = 0;
			    
			    //Store in Local DB
			    sprintf(buf1, "INSERT INTO ContentInstance (rqi, con, cnf, _to)"\
			    " VALUES ('%s', '%s', '%s', '%s');", rqi.c_str(), con.c_str(), cnf.c_str(), _to); 
			    
			    //Set Topic to /oneM2M/req/+/CSE_01
			    create_Topic("resp", "SAE02", "CSE_01");
			break;
			
			case 23:	//SUBSCRIPTION (announceableSubordinateResource)  
			    printf("\n -----------Generating SUBSCRIPTION response  -----------\n");
			    //Create response code for SUBSCRIPTION
			    RSub.notificationURI = nu;
			    RSub.notificationContentType = nct;
			    RSub.notificationEventType = net;
			    
			    //Store in Local DB
			    sprintf(buf1, "INSERT INTO Subscription (rn, rqi, nu, net, nct, _to)"\
			    " VALUES ('%s', '%s', '%s', %d, %d, '%s');", rn.c_str(), rqi.c_str(), nu.c_str(), net, nct, _to); 
			    
			    //Set Topic to /oneM2M/resp/+/CSE_01
			    create_Topic("resp", "SAE02", "CSE_01");
			break;
		    }
		    rc = sqlite3_exec(db, buf1, callback, 0, &zErrMsg);
		    if( rc != SQLITE_OK ) {
		       fprintf(stderr, "SQL error: %s\n", zErrMsg);
		       sqlite3_free(zErrMsg);
		       Resp.responseStatusCode = 4000; 	///TODO: MAP SQL ERROR to Response Status Code
		    } 
		    else{
			fprintf(stdout, "\n -----------Operation done successfully -----------\n");
			Resp.responseStatusCode = 2001;
		    }
		    buf = Create_Resp(Resp);
		    //Publish Response
		    sleep(2);
		    publish(client, buf.c_str());
		    
		break;
		
		case 2:			//RETRIVE
		    //op, fr, to, rqi
		    i = 0;
		    strcpy(temp1, to.c_str());
		    str_tok = strtok (temp1, "/");
		    while (str_tok != NULL){
			to1[i] = str_tok;
			printf("\n%d: _to:%s\n",i, to1[i]);
			str_tok = strtok(NULL, "/");
			i++;
		    } 
		    printf("%d: To: %s\r\n", i, to.c_str());
		    if (i == 1)		//Retrive AE
		    {
			sprintf(buf1, "SELECT * FROM Registration WHERE aei = '%s';", From.c_str());
			rc = sqlite3_exec(db, buf1, callback, 0, &zErrMsg);
			if( rc != SQLITE_OK ) {
			   fprintf(stderr, "SQL error: %s\n", zErrMsg);
			   Resp.responseStatusCode = 4000; 	///TODO: MAP SQL ERROR to Response Status Code
			   sqlite3_free(zErrMsg);
			} 
			else{ 
			    Resp.responseStatusCode = 2000;
			}
		    }
		    //Set Topic to /oneM2M/resp/--/CSE_01
		    create_Topic("resp", "SAE02", "CSE_01");
		    buf = Retrive_Resp(Resp);
		    printf("RESP BUFFER: %s\r\n", buf.c_str());
		    //Publish Response
		    sleep(2);
		    publish(client, buf.c_str());
		
		break;
		
		case 3:			//UPDATE
		//op, to, fr, rqi, content
		break;
		
		case 4:			//DELETE
		    i = 0;
		    strcpy(temp1, to.c_str());
		    str_tok = strtok (temp1, "/");
		    while (str_tok != NULL){
			to1[i] = str_tok;
			printf("\n%d: _to:%s\n",i, to1[i]);
			str_tok = strtok(NULL, "/");
			i++;
		    } 
		    printf("%d: To: %s\r\n", i, to.c_str());
		    if (i == 2){ 		///Delete AEI
			
		    }
		     
		    //Delete Container for current scenario
		    if (i == 3){		/// Check and notify the Subscribed nodes to the container 
			//Check the AEID from URI in DB
			sprintf(buf1, "SELECT * FROM Registration WHERE CSE = '%s';", to1[1]);
			rc = sqlite3_exec(db, buf1, callback, 0, &zErrMsg);
			if( rc != SQLITE_OK ) {
			   fprintf(stderr, "SQL error: %s\n", zErrMsg);
			   sqlite3_free(zErrMsg);
			} 
			else{ //AEID found successfully Delete Container
			    fprintf(stdout, "\n\r AEID found successfully\r\n");
			    sprintf(buf1, "DELETE FROM Container WHERE rn = '%s';", to1[2]); 
		    
			    rc = sqlite3_exec(db, buf1, callback, 0, &zErrMsg);
			    if( rc != SQLITE_OK ) {
			       fprintf(stderr, "SQL error: %s\n", zErrMsg);
			       sqlite3_free(zErrMsg);
			       Resp.responseStatusCode = 4000; 	///TODO: MAP SQL ERROR to Response Status Code
			    } 
			    else{
				fprintf(stdout, "\n\r Container Delete Operation done successfully\r\n");
				Resp.responseStatusCode = 2002;
			    }
			}
		    }
		    
		    //Delete Subscription for current scenario
		    if (i == 4){		
			//Check the AEID from URI in DB
			sprintf(buf1, "SELECT * FROM Container WHERE rn = '%s';", to1[2]);
			rc = sqlite3_exec(db, buf1, callback, 0, &zErrMsg);
			if( rc != SQLITE_OK ) {
			   fprintf(stderr, "SQL error: %s\n", zErrMsg);
			   sqlite3_free(zErrMsg);
			} 
			else{ //AEID found successfully Delete Container
			    fprintf(stdout, "\n\r Container found successfully\r\n");
			    sprintf(buf1, "DELETE FROM Subscription WHERE rn = '%s';", to1[3]); 
		    
			    rc = sqlite3_exec(db, buf1, callback, 0, &zErrMsg);
			    if( rc != SQLITE_OK ) {
			       fprintf(stderr, "SQL error: %s\n", zErrMsg);
			       sqlite3_free(zErrMsg);
			       Resp.responseStatusCode = 4000; 	///TODO: MAP SQL ERROR to Response Status Code
			    } 
			    else{
				fprintf(stdout, "\n\r Subscription Delete Operation done successfully\r\n");
				Resp.responseStatusCode = 2002;
			    }
			}
		    }

		    //Set Topic to /oneM2M/resp/--/CSE_01
		    create_Topic("resp", "SAE02", "CSE_01");
		    buf = Delete_Resp(Resp);
		    printf("RESP BUFFER: %s\r\n", buf.c_str());
		    //Publish Response
		    sleep(2);
		    publish(client, buf.c_str());
		    
		break;
		
		case 5:			//NOTIFY
		break;
		
		default:
		printf("\n No valid Operation \n");
	    }
	    //Reset Parameters
	    delete temp1;
	    op = 0;
	    ty = 0;
	}
	
        if(notify){
            Request Req;
            Req.To = AE_ID; //put AE_ID of the subscribed node 
            Req.From = CSE_ID;
            Req.Request_Identifier = "m_notify01";
            Req.Operation = 5;
            Ntfy.subscriptionReference = sur;
            Ntfy.notificationEventType = net;
            Ntfy.content = con;
            Ntfy.contentInfo = cnf;
            buf = Notify(Req);
            //Set Topic to /oneM2M/req/SAE01/CSE_01
            create_Topic("req", "SAE02", "CSE_01");
            //Publish Notify to 
	    sleep(5);
            publish(client, buf.c_str());
                
            notify = false;
            //wait for Notification Response
            while(1)
            {
                if(rsc != 0){ 
                    //reg_resp = true;
                    printf("rsc = %d\n",rsc);
                    break;
                }
                else rsc = 0;
            }
            if(rsc == 2000)
                printf("Notification Done wth response: %s\n", response.c_str());
            else 
                printf("Notification failed with response: %s\n", response.c_str());
        }
    }
    
    sqlite3_close(db);    
  
    MQTTClient_disconnect(client, 10000);
    MQTTClient_destroy(&client);   
    
    return 0;
	
}
