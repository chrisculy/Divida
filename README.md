divida
======
[![Build Status](https://travis-ci.org/chrisculy/divida.svg?branch=master)](https://travis-ci.org/chrisculy/divida)

A library for dividing up costs for group activities such as shared groceries or camping trips.

Example Usage
=============

 Begin by creating a group that represents the people who are sharing expenses.
```cpp
auto group = divida::group("Camping Friends");
```

Create each of the persons in the group.
```cpp
auto arav = group.person("Arav Jindal");
auto marco = group.person("Marco Sanchez");
auto grace = group.person("Grace Yun");
auto maggie = group.person("Maggie McDonald");
```

Create the expenses that will be shared across the group. There may be an expense where everyone benefits equally from all the items: 
```cpp
auto expenseFood = std::make_unique<divida::expense>("Food", divida::date::create(12, 7, 2009), grace);
expenseFood->add_items(
    { { "Apples", 4.67f },
    { "Hot dogs", 8.55f },
    { "Hot dog buns", 4.36f },
    { "Beans", 3.79f },
    { "Trail mix", 9.82f },
    { "Potato chips", 5.03f } },
    { divida::beneficiary{ arav }, divida::beneficiary{ marco }, divida::beneficiary{ grace }, divida::beneficiary{ maggie } }
);
```

There also may be an expense where some people benefit differently. For example, if the camping trip was for 4 nights and Marco had to leave one night early, the campsites cost might be split up like so:
```cpp
auto expenseCampsites = std::make_unique<divida::expense>("Campsites", divida::date::create(13, 7, 2009), arav);
expenseCampsites->add_item({ "Campsite permit", 183.45f, { divida::beneficiary{ arav, 4.0f }, divida::beneficiary{ marco, 3.0f }, divida::beneficiary{ grace, 4.0f }, divida::beneficiary{ maggie, 4.0f } } });
```

Sometimes, there may be an expense where only some people benefit and each item benefits different people to a different degree. For example, Maggie may go and buy camping supplies for everyone including a tent for her and Grace to use, a headlamp for Marco, a tarp for Arav, and some firewood for everyone to share. However, they end up only using half of it and Grace takes the rest home:
```cpp
auto expenseCampingSupplies = std::make_unique<divida::expense>("Camping supplies", divida::date::create(10, 7, 2009), maggie);
expenseCampingSupplies->add_item({ "Two person tent", 95.78f,{ divida::beneficiary{ maggie }, divida::beneficiary{ grace } } });
expenseCampingSupplies->add_item({ "Headlamp", 14.56f, { divida::beneficiary{ marco } } });
expenseCampingSupplies->add_item({ "Tarp", 7.60f, { divida::beneficiary{ arav } } });
expenseCampingSupplies->add_item({ "Hiking boots", 32.14f, { divida::beneficiary{ maggie } } });
expenseCampingSupplies->add_item({ "Firewood", 12.00f, { divida::beneficiary{ arav }, divida::beneficiary{ marco }, divida::beneficiary{ grace, 5.0 }, divida::beneficiary{ maggie } } });
```

Now that all the expenses have been created, we create a report and add the expenses to it.
```cpp
auto report = group.report("Pacific Crest Trail Camping Trip");

report->add_expense(std::move(expenseFood));
report->add_expense(std::move(expenseCampsites));
report->add_expense(std::move(expenseCampingSupplies));
```

Finally, we calculate who should pay who and how much and print it out ...
```cpp
auto transactions = report->run();

for (auto & transaction : transactions)
    std::cout << transaction << "\n";
```

... resulting in the following output:
```
[[Grace Yun] pays $77.15 to [Arav Jindal]]
[[Marco Sanchez] pays $39.23 to [Arav Jindal]]
[[Marco Sanchez] pays $22.57 to [Maggie McDonald]]
```

Development Setup
=================

To begin developing for divida, run the `projects/generate.py <platform>` script to generate your platform's project files (where `<platform>` is one of `win`, `mac`, `linux`); the resulting files will be located in a platform subfolder of the `projects` folder (e.g. `projects/win`).

To keep your locally generated projects in sync with changes from git, there are provided git hooks that can be installed using the `hooks/setup.sh` script (runnable from Git Bash on Windows or any standard Bash shell on Linux or macOS). This only needs to be run once and any future changes will trigger automatic local project regeneration when changes are pulled down using git.

Note: when editing the CMake project files, any new CMake files must be added to the `projects/cmake.project` file to ensure the automatic git hooks work correctly.
