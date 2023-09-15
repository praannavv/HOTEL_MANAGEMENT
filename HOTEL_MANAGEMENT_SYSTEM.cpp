#include <iostream>
#include <ctype.h>
#include <string>
#include <cstring>
#include <set>
#include <cctype>
#include<conio.h>
using namespace std;

void menu()
{
    cout << "\t\t\t\t\t\t_______________________________";
    cout << "\n\t\t\t\t\t\t|         MAIN MENU           |";
    cout << "\n\t\t\t\t\t\t-------------------------------";
    cout << "\n\t\t\t\t\t\t1. BOOK ROOM ";
    cout << "\n\t\t\t\t\t\t2. DISPLAY ALL DATA ";
    cout << "\n\t\t\t\t\t\t3. DISPLAY DATA OF ROOM BOOKED FOR BILLING";
    cout << "\n\t\t\t\t\t\t4. DELETE RECORDS ";
    cout << "\n\t\t\t\t\t\t5. MODIFY RECORDS";
    cout << "\n\t\t\t\t\t\t6. DISPLAY TOTAL ROOMS BOOKED";
    cout << "\n\t\t\t\t\t\t7. SORT BY ROOM NUMBER";
    cout << "\n\t\t\t\t\t\t8. EXIT";
}

void Modify()
{
    
    cout << "\n\t\t\t\t\t\t1. ROOM NUMBER";
    cout << "\n\t\t\t\t\t\t2. ID ";
    cout << "\n\t\t\t\t\t\t3. PHONE NUMBER ";
	cout << "\n\t\t\t\t\t\t4. NUMBER OF STAY ";
    cout << "\n\t\t\t\t\t\t5. EXIT";
   
}
void press_any_Key(){
	cout<<"\n\n\n\n\t\t\t\t\t\tPress Any Key to Continue..............";
}
class Node
{
public:
    int id;
    int Room_no;
    char Phone_no[10];
    string name;
    int date;
    Node *next;

    Node()
    {
        next = NULL;
    }

    Node(int room_no, const char *number, int id, const string &name,int date)
    {
        this->Room_no = room_no;
        this->id = id;
        strcpy(Phone_no, number);
        this->name = name;
        this->date=date*10;
        next = NULL;
    }

    int get_id()
    {
        return this->id;
    }

    void showdata()//to show all data
    {
        cout << "\n\n\t\t\t\t\t\tROOM NUMBER = " << Room_no;
        cout << "\n\t\t\t\t\t\tID = " << id;
        cout << "\n\t\t\t\t\t\tNAME = " << name;
        cout << "\n\t\t\t\t\t\tPhone Number = " << Phone_no;
    }
    void showdata_for_bill(){
    	cout<<"\n\n\t\t\t\t\t\tfor Room Number "<<Room_no<<" Bill is $"<<date;
	}
};

class LinkedList
{
    Node *head = NULL;
    set<int> usedRoomNumbers;
    set<int> usedIds;
    set<string> usedPhoneNumbers;

public:
	static int count;
	Node *merge(Node *left, Node *right)
    {
        Node *mergedList = NULL;
        Node **current = &mergedList;

        while (left != NULL && right != NULL)
        {
            if (left->Room_no <= right->Room_no)
            {
                *current = left;
                left = left->next;
            }
            else
            {
                *current = right;
                right = right->next;
            }
            current = &((*current)->next);
        }

        // Append the remaining nodes (if any)
        *current = (left != NULL) ? left : right;

        return mergedList;
    }

    // Merge sort function for linked lists
    Node *mergeSort(Node *head)
    {
        if (head == NULL || head->next == NULL)
            return head;

        Node *middle = getMiddle(head);
        Node *left = head;
        Node *right = middle->next;
        middle->next = NULL; // Split the list into two halves

        left = mergeSort(left);
        right = mergeSort(right);

        return merge(left, right);
    }

    // Helper function to find the middle of a linked list
    Node *getMiddle(Node *head)
    {
        if (head == NULL)
            return NULL;

        Node *slow = head;
        Node *fast = head;

        while (fast->next != NULL && fast->next->next != NULL)
        {
            slow = slow->next;
            fast = fast->next->next;
        }

        return slow;
    }

    
    bool Check_available_room(int room_no)
    {
        // Check if the room number is already used
        if (usedRoomNumbers.count(room_no) > 0)
        {
            return true;
        }
        return false;
    }
	
    bool Check_id(int id)
    {// Check if id is already used
        if (usedIds.count(id) > 0)
        {
            return true;
        }
        return false;
    }
    bool check_phone_no(const string &number)
    {
	//Check if Phone Number is in use.
        if (usedPhoneNumbers.count(number) > 0)
        {
            return false;
        }
        return true;
    }
	void for_bill(){//This is used to show bill 
		if(head==NULL){
			cout<<"\n\n\t\t\t\t\tNO Room is Booked Till now";
			return;
		}
		Node* temp=head;
		while(temp!=NULL){
			temp->showdata_for_bill();
			temp=temp->next;
		}
	}
	void for_bill_indi(int rm){
		Node* temp=head;
		while(temp){
			if(temp->Room_no==rm){
			temp->showdata_for_bill();
			return;
		}
			temp=temp->next;
		}
		cout<<"\n\n\t\t\t\t\t\tRoom is Not booked";	
	}
	
    void Book_Room(int room_no, const string &number, int id, const string &name,int date)
    {
        // Check if the room number, ID, and phone number are already used
        if (Check_available_room(room_no) || Check_id(id) || !check_phone_no(number))
        {
            cout << "\t\t\t\tCannot book this room. Please enter unique details." << endl;
            return;
        }

        Node *newnode = new Node(room_no, number.c_str(), id, name,date);
        if (head == NULL)
        {
            head = newnode;
            count++;
            usedIds.insert(id);
            usedPhoneNumbers.insert(number);
            usedRoomNumbers.insert(room_no); // Add the used room number to the set
            return;
        }

        Node *temp = head;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = newnode;
        count++;
        usedIds.insert(id);
        usedPhoneNumbers.insert(number);
        usedRoomNumbers.insert(room_no);
    }
	void sort_by_room_no(){	
		
        if (head == NULL || head->next == NULL)
            return;

        head = mergeSort(head);
    	
	}
	void Check_indi_booked_rooms(int rm){
		Node *temp = head;
        while (temp != NULL)
        {
            if(temp->Room_no==rm){
            	temp->showdata();
            	return;
			}
            temp = temp->next;
        }
        cout<<"\n\t\t\t\t\t\tNo Room is Booked for this Room Number";
    }
	
    void Check_all_booked_rooms()
    {
    	if(head==NULL){
    		cout<<"\n\t\t\t\t\t\t\t\t\tNo Room is Booked";
		}
        Node *temp = head;
        while (temp != NULL)
        {
            temp->showdata();
            temp = temp->next;
        }
    }
void Delete_Last_Booked_Room()
{
	if(head==NULL){
		cout<<"\n\n\t\t\t\t\t\t\tNo Room Booked";
		return;
	}
    if (head == NULL || head->next == NULL)
    {
        // The list is empty or has only one node
        if (head != NULL)
        {
            usedIds.erase(head->id);
            usedPhoneNumbers.erase(head->Phone_no);
            usedRoomNumbers.erase(head->Room_no);
            delete head;
            head = NULL;
            count--;
            
        }
        cout<<"\n\n\t\t\t\t\t\tOperation performed successfully";
        return;
    }

    Node *temp = head;
    while (temp->next->next != NULL)
    {
        temp = temp->next;
    }

    // Now, temp points to the second-to-last node
    usedIds.erase(temp->next->id);
    usedPhoneNumbers.erase(temp->next->Phone_no);
    usedRoomNumbers.erase(temp->next->Room_no);
    delete temp->next;
    temp->next = NULL;
    count--;
    cout<<"\n\n\t\t\t\t\tOperation done succesfully";
}
    void Delete_Recently_Booked_Room()
    {
        if (head == NULL)
        {
            return;
        }
        Node *temp = head;
        head = temp->next;
        temp->next = NULL;
        delete (temp);
        count--;
    }

void Remove_Booked_Room(int position)
    {
        if (head == NULL)
        {
            cout<<"\n\n\t\t\t\t\t\tNO ROOM BOOKED";
			return;
        }
        Node *temp = head;
        if (position == head->Room_no)
        {
            usedIds.erase(head->id);

            usedPhoneNumbers.erase(head->Phone_no);
            usedRoomNumbers.erase(head->Room_no);
            Delete_Recently_Booked_Room();
            cout<<"\n\n\t\t\t\t\t\tOperation performed successfully";
            return;
        }
        while (temp->next && temp->next->get_id() != position)
        {
            temp = temp->next;
        }
        if (!temp->next)
        {
           cout<<"\n\n\t\t\t\t\t\tRoom not found";
		    return; // Room  not found
        }

        Node *temp2 = temp->next;
        usedIds.erase(temp2->id);
        usedPhoneNumbers.erase(temp2->Phone_no);
        usedRoomNumbers.erase(temp2->Room_no);
        temp->next = temp->next->next;
        delete (temp2);
        count--;
        cout<<"\n\n\t\t\t\t\t\tOperation performed successfully";
    }
    void update_id(int curr_id,int new_id){
    	 if (head == NULL)
        {
            return;
        }
        Node *temp = head;
       while(temp){
       	if(temp->id==curr_id){
       		temp->id=new_id;
       		usedIds.erase(curr_id);
	   		usedIds.insert(new_id);
       		return;
		   }
		   temp=temp->next;
	   }
	   
	}
	void update_room_no(int curr_rm,int new_rm){
    	 if (head == NULL)
        {
            return;
        }
        Node *temp = head;
       while(temp){
       	if(temp->Room_no==curr_rm){
       		temp->Room_no=new_rm;
       		 usedRoomNumbers.erase(curr_rm);
	   		usedRoomNumbers.insert(new_rm);
       		return;
		   }
		   temp=temp->next;
	   }
	  
	}
//Updating Phone Number
void update_Phone_no(const char curr_ph[11], const char new_ph[11]) {
    if (head == NULL) {
        return;
    }
    Node* temp = head;
    while (temp) {
        if (strcmp(temp->Phone_no, curr_ph) == 0) {
            for(int i=0;i<10;i++){
            	temp->Phone_no[i]=new_ph[i];
			}
				usedPhoneNumbers.erase(curr_ph);
   				 usedPhoneNumbers.insert(new_ph);
   				 return;
        }
        temp = temp->next;
    }
    
}

void total_room_booked() {
    int numberOfRoomNumbers = usedRoomNumbers.size();
    cout << "\n\n\t\t\t\t\t\tNumber of Room Numbers: " << numberOfRoomNumbers << endl;

}
void update_stay(int id, int days) {
    Node* temp = head;
    while (temp != NULL) {
        if (temp->id == id) {
            temp->date += days * 10;
            cout<<"\n\n\t\t\t\t\t\tUpdated successfully";
            return; 
        }
        temp = temp->next;
    }
   
    cout << "\n\n\t\t\t\t\t\tUser with ID " << id << " not found." << endl;
}

};
int LinkedList::count = 0;

bool isValidPhoneNumber(const char *phoneNumber)
{
    if (strlen(phoneNumber) != 10)
    {
        return false;
    }
    for (int i = 0; phoneNumber[i] != '\0'; ++i)
    {
        if (!isdigit(phoneNumber[i]))
        {
            return false;
        }
    }
    return true;
}
bool isAlphaString(const string& name) {
    for (int i=0;i<name.length();i++) {
    	char c=name[i];
    	if(c==' '){continue;
		}
        if (!isalpha(c)) {
            return false; 
        }
    }
    return true;
}

int main()
{
    LinkedList ll;
    menu();
    int choice;
repeat:	
    cout << "\n\n\t\t\t\t\t\tEnter Your choice = ";
    cin >> choice;

    if (choice == 1)
    {
        int id;
        int Room_no;
        char phoneNumber[11];
        string name;
        int date;
    id_try_again:
        cout << "\t\t\t\t\t\tEnter a valid ID = ";
        cin >> id;
        if (ll.Check_id(id))
        {

            cout << "\t\t\t\tThis ID is already in use. Please enter a unique ID." << endl;
            goto id_try_again;
        }
    room_no_try_again:
        cout << "\t\t\t\t\t\tEnter Room Number = ";
        cin >> Room_no;
        if(Room_no>30){
        	cout<<"\t\t\t\tWe Don't have that much roomm our hotel select room from 1 to 30\n";
        	goto room_no_try_again;
		}
        if (ll.Check_available_room(Room_no))
        {
            cout << "\t\t\t\tThis Room is already occupied, Try Another One\n";
            goto room_no_try_again;
        }

    phone_try_again:
        cout << "\t\t\t\t\t\tEnter a 10-digit phone number: ";
        cin >> phoneNumber;
        if (isValidPhoneNumber(phoneNumber) && ll.check_phone_no(phoneNumber))
        {
        }
        else
        {
            cout << "\t\t\t\tInvalid phone number. Please enter a valid 10-digit number.\n"
                 << endl;
            goto phone_try_again;
        }
        repeat_name:
        cout << "\t\t\t\t\t\tEnter name: ";
        cin.ignore();
        getline(cin, name);
        if(isAlphaString(name)){ 
		
        cout<<"\t\t\t\t\t\tHow Long You want to Stay in our hotel (days) = ";cin>>date;
        ll.Book_Room(Room_no, phoneNumber, id, name,date);
        cout<<"\n\n\t\t\t\t\t\tAll the detail is been added ";}
        else{
        	cout << "\t\t\t\t\t\tInvalid name";
        	
		}
        
    }
    else if (choice == 2)
    {
    	int select;
    	cout << "\n\n\t\t\t\t\t\t1. Details of Every Room Booked " ;
        cout << "\n\t\t\t\t\t\t2. Details of Indiviual Room  " ;
        cout << "\n\n\t\t\t\t\t\tEnter Option = ";
        cin>>select;
        switch(select){
        	case 1:
        		ll.Check_all_booked_rooms();
        		break;
        	case 2:
        		int rm;
        		cout<<"\n\t\t\t\t\t\tEnter Room Number = ";cin>>rm;
        		ll.Check_indi_booked_rooms(rm);
        		break;
        	default:
        		cout<<"\n\n\t\t\t\t\tInvalid Option Selected";
        		break;
        	
		}
    }
    else if(choice == 3){
    	int select;
    	cout << "\n\n\t\t\t\t\t\t1. Bill of Every Room Booked " ;
        cout << "\n\t\t\t\t\t\t2. Bill of Indiviual Room  " ;
        cout << "\n\n\t\t\t\t\t\tEnter Option = ";
        cin>>select;
        switch(select){
        	case 1:
        		ll.for_bill();
        		break;
        	case 2:
        		int rm;
        		cout<<"\n\t\t\t\t\t\tEnter Room Number = ";cin>>rm;
        		ll.for_bill_indi(rm);
        		break;
        	default:
        		cout<<"\n\n\t\t\t\t\tInvalid Option Selected";
        		break;
        	
		}
	     
	}
    else if (choice == 4)
    {
    	int select;
    	cout << "\n\n\t\t\t\t\t\t1. Delete Recently Room Booked " ;
        cout << "\n\t\t\t\t\t\t2. Delete  Indiviual Room Booked " ;
        cout << "\n\n\t\t\t\t\t\tEnter Option = ";
        cin>>select;
        switch(select){
        	case 1:
        		ll.Delete_Last_Booked_Room();
        		break;
        	case 2:
        		int rm;
        		cout<<"\n\t\t\t\t\t\tEnter Room Number = ";cin>>rm;
        		ll.Remove_Booked_Room(rm);
        		
        		break;
        	default:
        		cout<<"\n\n\t\t\t\t\tInvalid Option Selected";
        		break;
        	
		}
    }
    else if (choice == 5)//Modify
    {
    	cout<<"\n\n\t\t\t\t\t\tEnter Room Number = ";
    	int get_rm;
    	cin>>get_rm;
    	if(ll.Check_available_room(get_rm)){
    	repeat_update:
    	Modify();
    	int choice;
		cout << "\n\n\t\t\t\t\t\tEnter Your choice = ";
    	cin >> choice;
    	if(choice==1){
    	int room_no;
			new_room_no:
			cout<<"\n\t\t\t\t\t\tEnter New Room Number = ";cin>>room_no;
			if(ll.Check_available_room(room_no)){
				cout<<"\n\t\t\t\t\t\tThis Room is alreay occupied\n";
				goto new_room_no;
			}
			else{
				//function to change room _number;
				ll.update_room_no(get_rm,room_no);
			}
		}
		
		else if(choice ==2){
			int curr_id,new_id;
    		
    		cout<<"\n\t\t\t\t\t\tEnter Your Current Id = ";cin>>curr_id;
    		if(ll.Check_id(curr_id)){
			new_id:
			cout<<"\n\t\t\t\t\t\tEnter New Id = ";cin>>new_id;
			if(ll.Check_id(new_id)){
				cout<<"\n\t\t\t\t\t\tId regonization denied\n";
				goto new_id;
			}
			else{
				//function to change id;
				ll.update_id(curr_id,new_id);
				
			}
		}
		else{
			cout<<"\n\t\t\t\t\t\tInvalid Id  , Try again\n";
			
		}
		}
    	else if (choice == 3) {
    char curr_phone_no[11];char new_phone_no[11];

    cout << "\n\t\t\t\t\t\tEnter Your Phone Number = ";
    cin>>curr_phone_no;
    if (ll.check_phone_no(curr_phone_no)==false  ) {
        new_phone_no:
        cout << "\n\t\t\t\t\t\tEnter New Phone Number = ";
      
        cin>>new_phone_no;

        if (ll.check_phone_no(new_phone_no)==false && isValidPhoneNumber(new_phone_no)) {
            cout << "\n\t\t\t\t\t\tThis Phone Number is already in Use\n";
            goto new_phone_no;
        } else {
            // Call the function to change room number;
            ll.update_Phone_no(curr_phone_no, new_phone_no);
        }
    } else {
        cout << "\n\t\t\t\t\t\tSomething is Wrong Phone Number, Try again\n";
        
    }}


		else if(choice ==4){
			int days;
			cout<<"\n\n\t\t\t\t\t\tEnter the Number of stay to be increased = ";
			cin>>days;
			ll.update_stay(get_rm,days);
    		
		}
		else if(choice==5){
			
		}
		else{
			system("cls");
			goto repeat_update;
		}
    }
	else{
    	cout<<"\n\n\t\t\t\t\t\t\tRoom isn't Booked";
    	
	}}
    
    else if(choice==6){
    	ll.total_room_booked();
    	
	}
	else if(choice==7){
		ll.sort_by_room_no();
		cout<<"\n\n\t\t\t\t\t\tOperation done succesfully";
	}
    else if (choice == 8)
    {
        goto Exit;
    }
    else
    {
        cout << "\n\t\t\t\t\t\tEnter a valid Option";
        getch();
        system("cls");
		menu();
        goto repeat;
    }
    press_any_Key();
    getch();
    system("cls");
    menu();
    goto repeat;
	Exit:
	system("cls");
	cout<<"\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\tTHANK YOU \n\n\n\n\n\n\n\n\n\n";
	press_any_Key();
	getch();
	
    return 0;
}
