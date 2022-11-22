#pragma once

#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <map>
#include <functional>
#include <algorithm>
#include <ctime>

#include "./struct.h"
#include "./data.h"
#include "./table.h"

using namespace structure;

namespace utility
{
  void cout(string color, string message, bool with_endl = true)
  {
    string hex = data::colors[color];
    string new_msg = hex + message + "\033[0m";
    with_endl ? std::cout << new_msg << endl : std::cout << new_msg;
  }

  string today()
  {
    time_t curr_time;
    tm *curr_tm;
    char date_string[100];
    time(&curr_time);
    curr_tm = localtime(&curr_time);
    strftime(date_string, 50, "%Y-%m-%d", curr_tm);
    return string(date_string);
  }

  bool isTimeLater(string first, string second)
  {
    return stoi(first) > stoi(second) || stoi(first) == stoi(second);
  }

  bool confirm(string message, bool is_formatted = true)
  {
    string is_confirmed = "t";
    string new_message = is_formatted ? "Data " + message + " tidak akan bisa dikembalikan lagi! (y/t): " : message;
    std::cout << endl;
    utility::cout("red", "Apa anda yakin?");
    utility::cout("red", new_message, false);
    cin >> is_confirmed;

    return is_confirmed == "y" || is_confirmed == "Y";
  }

  void header(string title, string subtitle = "")
  {
    system("cls");
    utility::cout("red", "\n\n=================================");
    utility::cout("red", title);
    if (subtitle != "")
    {
      utility::cout("white", subtitle);
    }
    utility::cout("red", "=================================");
  }

  string toLower(string word)
  {
    string transformed = word;
    transform(transformed.begin(), transformed.end(), transformed.begin(), ::tolower);
    return transformed;
  }

  void notify(string type, string message, bool with_suffix = true)
  {
    string new_message = with_suffix ? message + " [TEKAN ENTER]" : message;
    map<string, string> types = {
        {"success", "green"},
        {"error", "red"},
        {"warning", "yellow"},
        {"info", "cyan"},
    };
    utility::cout(types[type], new_message);
    getch();
  }

  size_t hash(string word)
  {
    std::hash<string> hashed;
    return hashed(word);
  }

  int count(Node *head)
  {
    int count = 0;        // Initialize count
    Node *current = head; // Initialize current
    while (current != NULL)
    {
      count++;
      current = current->next;
    }
    return count;
  }

  // * LINKED LIST UTILS
  void linkedListInsert(Node *&head, vector<string> data)
  {
    Node *node = new Node;
    node->data = data;
    node->next = head;
    head = node;
  }

  Node *linkedListTransform(vector<vector<string>> content)
  {
    Node *root = NULL;
    for (int row = 0; row < content.size(); row++)
    {
      utility::linkedListInsert(root, content[row]);
    }
    return root;
  }

  vector<vector<string>> linkedListConvert(Node *head)
  {
  }
  // * END OF LINKED LIST UTILS
  Node *list(string path)
  {
    fstream file;
    file.open(path, ios::in);
    vector<vector<string>> content;
    vector<string> row;
    string line, word;

    if (file.is_open())
    {
      while (getline(file, line))
      {
        row.clear();
        stringstream str(line);
        while (getline(str, word, ','))
          row.push_back(word);
        content.push_back(row);
      }
    }
    else
    {
      utility::notify("error", "File tidak ada!");
    }
    file.close();
    Node *root = utility::linkedListTransform(content);
    return root;
  }

  vector<string> latest(string path)
  {
    Node *head = utility::list(path);
    while (head->next != NULL)
      head = head->next;
    return head->data;
  }
  Node *SortedMerge(Node *a, Node *b, int attribute, int type);
  void FrontBackSplit(Node *source, Node **frontRef, Node **backRef);
  /* sorts the linked list by changing next pointers (not data) */
  void MergeSort(Node **headRef, int attribute, int type)
  {
    Node *head = *headRef;
    Node *a;
    Node *b;
    /* Base case -- length 0 or 1 */
    if ((head == NULL) || (head->next == NULL))
    {
      return;
    }
    /* Split head into 'a' and 'b' sublists */
    FrontBackSplit(head, &a, &b);
    /* Recursively sort the sublists */
    MergeSort(&a, attribute, type);
    MergeSort(&b, attribute, type);
    /* answer = merge the two sorted lists together */
    *headRef = SortedMerge(a, b, attribute, type);
  }
  /* See https:// www.geeksforgeeks.org/?p=3622 for details of this
  function */
  Node *SortedMerge(Node *a, Node *b, int attribute, int type)
  {
    Node *result = NULL;
    bool isAsc = type == 1;
    bool condition = false;

    /* Base cases */
    if (a == NULL)
      return (b);
    else if (b == NULL)
      return (a);

    condition = isAsc ? a->data[attribute] <= b->data[attribute] : a->data[attribute] >= b->data[attribute];

    if (condition)
    {
      result = a;
      result->next = SortedMerge(a->next, b, attribute, type);
    }
    else
    {
      result = b;
      result->next = SortedMerge(a, b->next, attribute, type);
    }
    return (result);
  }
  /* UTILITY FUNCTIONS */
  /* Split the nodes of the given list into front and back halves,
  and return the two lists using the reference parameters.
  If the length is odd, the extra node should go in the front list.
  Uses the fast/slow pointer strategy. */
  void FrontBackSplit(Node *source, Node **frontRef, Node **backRef)
  {
    Node *fast;
    Node *slow;
    slow = source;
    fast = source->next;
    /* Advance 'fast' two nodes, and advance 'slow' one node */
    while (fast != NULL)
    {
      fast = fast->next;
      if (fast != NULL)
      {
        slow = slow->next;
        fast = fast->next;
      }
    }
    /* 'slow' is before the midpoint in the list, so split it in two
    at that point. */
    *frontRef = source;
    *backRef = slow->next;
    slow->next = NULL;
  }

  vector<vector<string>> sort(string path, int field, int type)
  {
    // vector<vector<string>> list = utility::list(path);
    // for(int i=0; i < list.size() - 1; i++) {
    //   for(int j=i+1; j < list.size(); j++) {
    //     // * 1 = ASC, 2 = DESC
    //     bool is_pass = type == 1 ? list[i][field] > list[j][field] : list[i][field] < list[j][field];
    //     if(is_pass) {
    //       vector<string> temp = list[j];
    //       list[j] = list[i];
    //       list[i] = temp;
    //     }
    //   }
    // }
    // return list;
  }

  int fibonacciSearch(Node *node, string x, int n, int idx)
  {
    int F0 = 0;
    int F1 = 1;
    int F = F0 + F1;
    while (F < n)
    {
      F0 = F1;
      F1 = F;
      F = F0 + F1;
    }
    int offset = -1;
    int trv = 0;
    while (F > 1)
    {
      Node *temp = node;
      int i = min(offset + F0, n - 1);
      while (temp->next != NULL && trv < i)
      {
        temp = temp->next;
        trv++;
      }
      if (temp->data[idx] < x)
      {
        F = F1;
        F1 = F0;
        F0 = F - F1;
        offset = i;
      }
      else if (temp->data[idx] > x)
      {
        F = F0;
        F1 = F1 - F0;
        F0 = F - F1;
      }
      else
        return i;
      trv = 0;
    }
    Node *temp2 = node;
    while (temp2->next != NULL && trv < offset + 1)
    {
      temp2 = temp2->next;
      trv++;
    }
    if (F1 && temp2->data[idx] == x)
      return offset + 1;
    return -1;
  }

  Node *search(string path, const std::initializer_list<int> &fields, string keyword, bool is_universal = false, bool is_exact = false)
  {
    vector<vector<string>> filtered;
    Node *head = utility::list(path);
    string compared;
    bool condition;

    keyword = utility::toLower(keyword);

    // for(int index = 0; index < list.size(); index++) {
    //   if(is_universal) {
    //     for(int second_index = 0; second_index < list[index].size(); second_index++) {
    //       compared = utility::toLower(list[index][second_index]);
    //       if(compared.find(keyword) != string::npos) {
    //         filtered.push_back(list[index]);
    //       }
    //     }
    //   } else {
    //     for (auto field : fields) {
    //       compared = utility::toLower(list[index][field]);
    //       condition = is_exact ? (compared == keyword) : (compared.find(keyword) != string::npos);
    //       if(condition) {
    //         filtered.push_back(list[index]);
    //       }
    //     }
    //   }
    // }
    return head;
  }

  vector<string> find(string path, const std::initializer_list<int> &fields, string keyword, bool is_exact = true)
  {
    // vector<string> empty;
    // vector<vector<string>> list = utility::search(path, fields, keyword, false, is_exact);
    // return list.empty() ? empty : list.back();
  }

  void update(string path, int field, int field_length, string identifier, string new_data[])
  {
    // fstream file;

    // identifier = utility::toLower(identifier);

    // vector<vector<string>> content = utility::list(path);

    // file.open(path, ios::out);
    // for(int row = 0; row < content.size(); row++) {
    //   string val;
    //   string compared = utility::toLower(content[row][field]);
    //   if(compared != identifier) {
    //     for(int col = 0; col < content[row].size(); col++) {
    //       val += content[row][col] + ",";
    //     }
    //   } else {
    //     for(int new_data_col = 0; new_data_col < field_length; new_data_col++) {
    //       val += new_data[new_data_col] + ",";
    //     }
    //   }
    //   val += "\n";
    //   file << val;
    // }
    // file.close();
  }

  void destroy(string path, int field, int field_length, string identifier)
  {
    // fstream file;

    // identifier = utility::toLower(identifier);

    // vector<vector<string>> content = utility::list(path);

    // file.open(path, ios::out);
    // for(int row = 0; row < content.size(); row++) {
    //   string val;
    //   string compared = utility::toLower(content[row][field]);
    //   if(compared != identifier) {
    //     for(int col = 0; col < content[row].size(); col++) {
    //       val += content[row][col] + ",";
    //     }
    //     val += "\n";
    //     file << val;
    //   }
    // }
    // file.close();
  }

  TextTable table(int cols, string headers[], Node *head)
  {
    TextTable table('-', '|', '+');
    if (head == NULL)
    {
      utility::notify("error", "Tidak ada data!");
    }

    // SET HEADERS
    for (int col = 0; col < cols; col++)
    {
      table.add(headers[col]);
    }
    table.endOfRow();

    // SET ROWS
    int row_nums = 1;
    while (head != NULL)
    {
      for (int col = 0; col < cols; col++)
      {
        string val = col != 0 ? head->data[col - 1] : to_string(row_nums);
        table.add(val);
      }
      table.endOfRow();
      head = head->next;
      row_nums++;
    }
    return table;
  }
};