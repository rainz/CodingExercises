#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <set>
#include <map>
#include "utils.h"

using namespace std;

/*
 * Problem Statement #2:
(Version: TwoSigmaCodeTestCopyFile $Revision: 1.9 $)

Oh no! Disaster has struck some of ACME's redundant data centers. The
administrators have managed to restore backups, but some data sets are
still missing from some data centers. Fortunately, every data set can be
found at least once in one or more of the data centers. However, before
ACME can resume normal operations, it needs to ensure that each data
center has a copy of every data set.

Your goal is to help ACME resume normal operations by writing a program to
synchronize data sets between data centers using as few copies as possible.

Input:
------
The first line of input will contain an integer between 0 and 999999
inclusive, representing the number of data centers.

Following that will be one line of input for each data center with a
space-separated list of data set ids currently present at that data center.
Data set ids are each an integer between 1 and 999999, inclusive.
Each line will be at most 1000 characters long.

A data center with no data sets is represented with a blank line. Data set
ids are not necessarily consecutive. The list of data sets will not be in
any particular order.

Output:
-------
The program must output an optimal data set copy strategy to ensure that
every data center has a copy of every data set. Output one line for every
copy instruction.

A copy instruction is of the form <data-set-id> <from> <to>, where
<data-set-id> is the data set id, <from> is the index of the data center
the data set will be copied from (1 = the first data center), and <to> is
the index of the data center to copy the data set to.

When there are no more copy instructions, the program must output the word
"done" on a line by itself.

There is often more than one correct output with minimal number of operations
for a given input, and any output that satisfies the requirements is valid.

Constraints:
------------
The code you submit must take input from stdin and produce output to stdout
as specified above. No other output is permitted. You can assume the input
will be valid. In the examples below, the text "Input:" and "Output:" (or
"One Possible Correct Output:") are not part of the output, and neither are
the blank lines.

Example 1:
----------
Input:
4
1 3 4
1 2 3
1 3
1 4 2

One Possible Correct Output:
2 2 1
4 1 2
2 2 3
4 4 3
3 1 4
done

Example 2:
----------
Input:
2
1 2
2 1

Output:
done

Example 3:
----------
Input:
3
1 3 4 5 7
1 3
2

One Possible Correct Output:
2 3 2
2 3 1
1 1 3
4 1 2
5 1 3
5 3 2
4 2 3
3 1 3
7 1 2
7 1 3
done

 *
 */

typedef set<int> DataGroup;
typedef vector<int> DataCenterList;
typedef map<int, DataCenterList> DataCenterMap;

// Pick a random center from a list of data centers for load balancing
int chooseRandomCenter(const vector<int> &centers)
{
  int size = centers.size();
  if (size == 0)
  {
    cerr << "Data center set size = 0! Should not happen." << endl;
    return -1;
  }

  // No need to call srand() since we just want to do load balancing
  int random_idx = rand() % size;
  return centers[random_idx];
}

int synchronizeData()
{
  cout << "Please enter input data:" << endl;

  // Get total number of data centers from input
  string line_in;
  getline(cin, line_in);
  int num_datacenters = atoi(line_in.c_str());

  if (num_datacenters < 0 || num_datacenters > 999999)
  {
    cerr << "Number of data centers must be between 0 and 999999!" << endl;
    return -1;
  }

  DataGroup all_data; // contains list of all data IDs
  vector<DataGroup> data_sets(num_datacenters); // data for each data center
  DataCenterMap data_center_map; // maps data IDs to list of data centers

  // Get data for each data center from input
  for (int i = 0; i < num_datacenters; ++i)
  {
    vector<string> str_vec;
    getline(cin, line_in);
    tokenize(line_in, str_vec);

    DataGroup& data_group = data_sets[i]; // data for this data center
    int str_count = str_vec.size();
    for (int j = 0; j < str_count; ++j)
    {
      int data_id = atoi(str_vec[j].c_str());
      if (data_id < 1 || data_id > 999999)
        continue; // invalid ID
      data_group.insert(data_id);
      all_data.insert(data_id); // build a list of all data IDs
      DataCenterList &center_list = data_center_map[data_id];
      center_list.push_back(i + 1); // data center ID is 1-based, so i+1
    }
  }

  // For each data center, find missing data and copy them from other centers
  for (int i = 0; i < num_datacenters; ++i)
  {
    DataGroup &current_set = data_sets[i];
    int num_missing = all_data.size() - current_set.size(); // only need to copy "num_missing" data sets

    // Find missing data
    for (DataGroup::const_iterator it = all_data.begin();
         num_missing > 0 && it != all_data.end(); ++it)
    {
      if (current_set.find(*it) == current_set.end())
      {
        // Data missing, need to copy
        int missing_id = *it;
        DataCenterMap::const_iterator map_it = data_center_map.find(missing_id);
        if (map_it == data_center_map.end())
        {
          cerr << "Warning: no data center contains data #" << missing_id
               << ", should not happen!" << endl;
          continue;
        }
        int copy_from = chooseRandomCenter(map_it->second);
        if (copy_from < 1)
          continue;
        int copy_to = i + 1; // data center ID is 1-based
        if (copy_from == copy_to)
        {
          cerr << "copy_from (" << copy_from << ") equals copy_to (" << copy_to
               << ")! Should not happen!" << endl;
          continue;
        }
        cout << missing_id << ' ' << copy_from << ' ' << copy_to << endl;
        --num_missing;
      }
    }
  }

  cout << "done" << endl;
  return 0;
}
