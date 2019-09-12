#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <array>
#include <sstream>
#include <algorithm>

using namespace std;

/*
Node class will hold the information about a node of the tree
Variables of node class :
1. _parent -> pointer to the parent of the nodes
2. _distance -> distance from the origin
3. _level -> level in the hierachy
4. _name -> Name of the node.
*/
class Node {
public:
  Node * _parent;
  int _distance;
  int _level;
  string _name;

  void set_pointer(Node * parent);
  void set_distance (int distance);
  void set_name(string name);
  void set_level(int level);
  int get_distance();
  void print();
};


vector <string *> graph_List; //stores the input state file
vector <Node *> fringe; //fringe to store active nodes under investigation
string GOAL;
int max_num_fringe;
int max_num_expanded;
int max_num_generated;
vector <string> visited;
int is_this_node_visited(Node * current_node)
{
  if (visited.empty())
  {
    return 0;
  }
  else
  {
    int i;
    for (i = 0; i <visited.size();i++)
    {
      if (current_node->_name.compare(visited[i])==0)
      {
        return 1;
      }
    }
    return 0;
  }
}

bool compare_Nodes( Node *n1,  Node *n2)
{
  return n1->_distance < n2->_distance;
}

void Node::print()
{
  ostringstream ss;
  ss<<_name<<" "<< _distance<<" " << _level;
  cout<<ss.str()<<endl;

}
int Node::get_distance()
{
  return _distance;
}
void Node::set_pointer(Node *parent)
{
  _parent = parent;
}
void Node::set_distance(int distance)
{
  _distance = distance;
}

void Node::set_name(string name)
{
  _name = name;
}
void Node::set_level(int level)
{
  _level = level;
}



void add_to_fringe(Node * curr)
{
  cout << "Added to Fringe: "<< curr->_name << " " <<curr->_level << " "<< curr->_distance << endl;
  fringe.push_back(curr);
  max_num_fringe++;
  max_num_generated++;


}

int expand_node()
{
  //cout<<"Fringe Size : "<< fringe.size()<<endl;
  if (fringe.empty())
  {
    cout << "Empty";
    return -1;
  }
  sort(fringe.begin(), fringe.end(),compare_Nodes);
  cout << "\nAt fringe\n"<<endl;
  for (int i =0; i <fringe.size();i++)
  {
    cout << fringe[i]->_name << " " <<fringe[i]->_level << " "<< fringe[i]->_distance << endl;
  }


  //fringe.back()->print();
  Node *expand_node= fringe[0];
  max_num_fringe--;
  if (GOAL.compare(expand_node->_name) == 0)
  return 1;
  else if( is_this_node_visited(expand_node))
  {
    cout << expand_node->_name << " is visited.";
    fringe.erase(fringe.begin());
    max_num_expanded++;
    return 0;
  }
  else
  {
    visited.push_back(expand_node->_name);
    string node_name = expand_node->_name;
    cout <<node_name<< "is being expanded\n";
    int i=0 ;
    while ( i < graph_List.size())
    {
      if(node_name.compare(graph_List[i][0])==0)
      {
        Node * temp = new Node;
        temp->set_name(graph_List[i][1]);
        temp->set_distance(expand_node->_distance + stoi(graph_List[i][2]));
        temp->set_level(expand_node->_level + 1);
        temp->set_pointer(expand_node);
        add_to_fringe(temp);
      }
      if(node_name.compare(graph_List[i][1])==0)
      {
        Node * temp = new Node;
        temp->set_name(graph_List[i][0]);
        temp->set_distance(expand_node->_distance + stoi(graph_List[i][2]));
        temp->set_level(expand_node->_level + 1);
        temp->set_pointer(expand_node);
        add_to_fringe(temp);

      }
      i++;
    }
    max_num_expanded++;
    fringe.erase(fringe.begin());
  }
  return 0;
}

void open_file(string input_File_Name)
{
  char delim = ' ';

  ifstream myfile (input_File_Name);
  if(!myfile) {
    cout << "Cannot open input file.\n";
    return;
  }

  string temp_Str;
  getline(myfile,temp_Str);
  while((temp_Str.compare("END OF INPUT") != 0) && myfile) {

    int i =0;
    istringstream ss(temp_Str);
    string token;
    string *line = new string[3];
    while(getline(ss, token, delim))
    {
      line[i++] = token;
    }
    graph_List.push_back(line);
    getline(myfile,temp_Str);
  }
  myfile.close();
}


void uniform_search (char ** argv)
{

  string input_File_Name = argv[1];
  open_file(input_File_Name);
  GOAL = argv[3]; //the node that we are searching for

  //creating the origin node which is the start point for the search.
  Node * origin = new Node;
  origin->set_name(argv[2]);
  origin->set_pointer((Node *) NULL);
  origin->set_distance(0);
  origin->set_level(0);



  add_to_fringe(origin);
  int result;
  do{
    result = expand_node();
  }
  while (result == 0);
  cout << "\nAt fringe\n"<<"Result ="<<result<<endl;
  for (int i =0; i <fringe.size();i++)
  {
    cout << fringe[i]->_name << " " <<fringe[i]->_level << " "<< fringe[i]->_distance << endl;
  }

  if(result == 1)
  {
    cout << "nodes expanded: "<< max_num_expanded<<endl;
    cout << "nodes generated: "<< max_num_generated<<endl;
    cout << "max nodes in memory: "<< max_num_fringe <<endl;
    cout << "distance: "<< fringe[0]->_distance <<".0 km"<<endl;
    cout << "route:"<<endl;
    Node *curr = fringe[0];
    std::vector<string> print_result;


    while (curr->_parent!= (Node *)NULL)
    {
      ostringstream ss;
      ss << curr->_parent->_name << " to " << curr->_name <<", " << curr->_distance - curr->_parent->_distance <<".0 km"<<endl;
      curr = curr->_parent;
      print_result.push_back(ss.str());
    }
    int i =0;
    for (i=print_result.size()-1;i>=0;i--)
    {
      cout<< print_result[i];
    }
  }
  else if (result == -1)
  {

    cout << "nodes expanded: "<< max_num_expanded<<endl;
    cout << "nodes generated: "<< max_num_generated<<endl;
    cout << "max nodes in memory: "<< max_num_fringe <<endl;
    cout << "No route found."<<endl;
  }



}


int main(int argc, char** argv)
{
  if (argc <3)
  {
    printf("Error!\n" );
  }
  else if (argc == 4)
  {
    uniform_search(argv);
  }

}
