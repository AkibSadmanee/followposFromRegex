#include<iostream>
#include<stack>
#include<vector>
using namespace std;

struct Foo{
  vector<int> firstpos;
  vector<int> lastpos;
  char symbol;
  bool nullable;
};

bool is_valid(string input);
int convert_to_postfix(string input, string &postfix);
int rankify(char op);
void compute_followpos(string postfix, int charCount);
vector<int> compute_fpos(char sym, Foo c1,Foo c2);
vector<int> compute_lpos(char sym, Foo c1,Foo c2);
bool check_nullable(char sym, bool c1, bool c2);
void display_stack(stack<Foo> foo);


int main(){

  string input;
  
  //Tests
  //string input = "(a|b.b)*.c*.#";
  //string input = "(a*.b.c*|x)*.#";
  
  //input
  cout<<"Enter Regular Expression (Infix format): ";
  cin>> input;
  
  //input validity check
  bool valid = is_valid(input);
  if(!valid){
    cout<<"Invalid input!!"<<endl;
    return 0;
  }

  //convert expression to POSTFIX and count characters
  string postfix;
  int charCount = convert_to_postfix(input, postfix);
  cout<<"Postfix: "<<postfix<<endl<<endl;
  
  //computes and display followpos
  compute_followpos(postfix, charCount);
  cout<<endl;

  return 0;
}

bool is_valid(string input){
  stack<char> bracket_balance;
  bracket_balance.push('0');
  //Check if the input string is valid or not
  for(int i = 1; i< input.size(); i++){
    if(input[0] == '.' || input[0] == '|' || input[0] == '#' || input[0] == ')')  {cout<<"1"<<endl; return false;}

    if(input[input.size() -1] != '#') {cout<<"2"<<endl; return false;}

    //if(input[i] == '(') bracket_balance.push('(');
    //if(input[i] == ')') bracket_balance.pop();

    if( (
          (input[i] == '.' || input[i] == '|' ) &&
          (input[i-1] == '|' || input[i-1] == '.')
        ) || 
        (input[i] == '#' && input[i-1] != '.') ||
        (input[i] == '.' && input[i-1] == '(') ||
        (input[i] == '|' && input[i-1] == '(') ||
        (input[i] == '*' && input[i-1] == '.') ||
        (input[i] == '+' && input[i-1] == '.') ||
        (input[i] == '*' && input[i-1] == '(') ||
        (input[i] == '+' && input[i-1] == '(') )  {cout<<"3"<<endl; return false;}
    
    if( ((input[i] >='a' && input[i] <= 'z') ||
        (input[i] >='A' && input[i] <= 'Z')  ||
        (input[i] >='0' && input[i] <= '9')) 
        &&
        ((input[i-1] >='a' && input[i-1] <= 'z') ||
        (input[i-1] >='A' && input[i-1] <= 'Z')  ||
        (input[i-1] >='0' && input[i-1] <= '9')  ||
        input[i-1] == ')' ) )  {cout<<"4"<<endl; return false;}
  }
  
 // if(bracket_balance.top() != '0') {cout<<"5"<<endl; return false;}
  return true;
}

int rankify(char op){
  switch(op){
    case '.':
      return 2;
      break;
    case '|':
      return 1;
      break;
    default:
      return -1;
      break;
  }
}

int convert_to_postfix(string input, string &postfix){
  stack<char> helper;
  int counter = 0;
  
  for(int i = 0; i < input.size(); i++){
    if(input[i] == '(') helper.push('(');

    else if((input[i] >='a' && input[i] <= 'z') ||
            (input[i] >='A' && input[i] <= 'Z') ||
            (input[i] >='0' && input[i] <= '9') ||
            input[i] == '#' ){
              postfix += input[i];
              counter++;
            }

    else if(input[i] == '*' || input[i] == '+') postfix += input[i];

    else if(input[i] == ')'){
      while(helper.top() != '(' && !helper.empty()){
        postfix += helper.top();
        helper.pop();
      }
      if(helper.top() == '(') helper.pop();
    }
    else{
      //if operand is found
      while(!helper.empty() && rankify(input[i]) <= rankify(helper.top())){
        postfix += helper.top();
        helper.pop();
      }
      helper.push(input[i]);
    }
  }

  //empty stack
  while(!helper.empty()){
    postfix += helper.top();
    helper.pop();
  }
  return counter;
}

vector<int> compute_fpos(char sym, Foo c1 ,Foo c2){
  vector<int> fpos;
  if(sym == '.'){
    if(c1.nullable){
      for(int i = 0; i < c1.firstpos.size(); i++){
        fpos.push_back(c1.firstpos[i]);
      }
      for(int i = 0; i < c2.firstpos.size(); i++){
        fpos.push_back(c2.firstpos[i]);
      }
      return fpos;
    }
    return c1.firstpos;
  }

  if(sym == '|'){
    for(int i = 0; i < c1.firstpos.size(); i++){
      fpos.push_back(c1.firstpos[i]);
    }
    for(int i = 0; i < c2.firstpos.size(); i++){
      fpos.push_back(c2.firstpos[i]);
    }
    return fpos;
  }
}

vector<int> compute_lpos(char sym, Foo c1 ,Foo c2){
  vector<int> lpos;
  if(sym == '.'){
    if(c2.nullable){
      for(int i = 0; i < c1.lastpos.size(); i++){
        lpos.push_back(c1.lastpos[i]);
      }
      for(int i = 0; i < c2.lastpos.size(); i++){
        lpos.push_back(c2.lastpos[i]);
      }
      return lpos;
    }
    return c2.lastpos;
  }
  if(sym == '|'){
    for(int i = 0; i < c1.lastpos.size(); i++){
      lpos.push_back(c1.lastpos[i]);
    }
    for(int i = 0; i < c2.lastpos.size(); i++){
      lpos.push_back(c2.lastpos[i]);
    }
    return lpos;
  }
}

bool check_nullable(char sym, bool c1, bool c2){
  if(sym == '.'){
    if(c1 && c2) return true;
    return false;
  }
  if(sym == '|'){
    if(c1 || c2) return true;
    return false;
  }
}

void compute_followpos(string postfix, int charCount){
  //calculate firstpos & lastpos
  int counter = 0;
  stack<Foo> poscalc_stack;
  vector<int> followpos[charCount+1];

  for(int i = 0; i< postfix.size(); i++){
    if( (postfix[i] >='a' && postfix[i] <= 'z') ||
        (postfix[i] >='A' && postfix[i] <= 'Z') ||
        (postfix[i] >='0' && postfix[i] <= '9') ||
        postfix[i] == '#'){
          Foo temp;
          temp.firstpos.push_back(++counter);
          temp.lastpos.push_back(counter);
          temp.nullable = false;
          temp.symbol = postfix[i];
          poscalc_stack.push(temp);
    }
    else if(postfix[i] == '.' || postfix[i] == '|'){
      Foo c1, c2, temp;
      //pop two tops from stack 
      c2 = poscalc_stack.top(), poscalc_stack.pop();
      c1 = poscalc_stack.top(), poscalc_stack.pop();
      
      //get firstpos and lastpos
      vector<int> fpos = compute_fpos(postfix[i], c1, c2);
      vector<int> lpos = compute_lpos(postfix[i], c1, c2);
      //check if nullable
      bool nullable = check_nullable(postfix[i], c1.nullable, c2.nullable);

      //setup new object
      temp.firstpos = fpos;
      temp.lastpos = lpos;
      temp.nullable = nullable;
      temp.symbol = postfix[i];

      //push new object to stack
      poscalc_stack.push(temp);

      //calculate followpos for concatenation
      if(postfix[i] == '.'){
        for(int j =0; j< c2.firstpos.size(); j++){
          for(int i =0; i< c1.lastpos.size(); i++){
            followpos[c1.lastpos[i]].push_back(c2.firstpos[j]);
          }
        }
      }
    }

    else if(postfix[i] == '*'){
      Foo c1, temp;

      //pop one top from stack
      c1 = poscalc_stack.top(), poscalc_stack.pop();
      
      //setup new object
      temp.firstpos = c1.firstpos;
      temp.lastpos = c1.lastpos;
      temp.nullable = true;
      temp.symbol = postfix[i];

      //push new object to stack
      poscalc_stack.push(temp);

      //calculate followpos for *
      for(int i =0; i< c1.firstpos.size(); i++){
        for(int j =0; j< c1.lastpos.size(); j++){
          followpos[c1.lastpos[j]].push_back(c1.firstpos[i]);
        }
      }
      
    }

    else if(postfix[i] == '+'){
      Foo c1, temp;

      //pop one top from stack
      c1 = poscalc_stack.top(), poscalc_stack.pop();
      
      //setup new object
      temp.firstpos = c1.firstpos;
      temp.lastpos = c1.lastpos;
      temp.nullable = false;
      temp.symbol = postfix[i];

      //push new object to stack
      poscalc_stack.push(temp);

      //calculate followpos for +
      for(int i =0; i< c1.firstpos.size(); i++){
        for(int j =0; j< c1.lastpos.size(); j++){
          followpos[c1.lastpos[j]].push_back(c1.firstpos[i]);
        }
      }
    }
  }
  
  //display followpos
  for(int i = 1; i <= charCount; i++){
    cout<<"Followpos("<<i<<") : { ";
    for(int j =0; j< followpos[i].size(); j++){
      cout<<followpos[i][j];
      if(j != followpos[i].size() -1) cout<<", ";
    }
    cout<<" }"<<endl;
  }
    
}
