#pragma once
#include <string>
#include <vector>
#include "produs.h"
#include "string.h"

void exportToCVS(const string& fName, const std::vector<Prod>& produse);

void exportToHTML(const string& fName, const std::vector<Prod>&produse);

