/*

Copyright (C) 2010-2013 KWARC Group <kwarc.info>

This file is part of MathWebSearch.

MathWebSearch is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

MathWebSearch is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with MathWebSearch.  If not, see <http://www.gnu.org/licenses/>.

*/
/**
 * @file engine_rep_qvar1.cpp
 *
 */

#include <string>
#include <cerrno>

#include "engine_tester.hpp"

using namespace mws;
using namespace std;

/*

index: f(h,h,t): (apply,4) (f,0) (h,0) (h,0) (t,0)
query: f(h,h,t): (apply,4) (f,0) (P,0) (P,0) (t,0)

1 solution expected

*/
static int g_num_hits;

struct Tester {
static
MwsIndexNode* create_test_MwsIndexNode() {
    MwsIndexNode* data = new MwsIndexNode();

    MwsIndexNode* h_node_1 = new MwsIndexNode();
    h_node_1->solutions = 1;
    data->children.insert(make_pair(h_ni, h_node_1));

    MwsIndexNode* f_node_1 = new MwsIndexNode();
    f_node_1->solutions = 1;
    data->children.insert(make_pair(f_ni, f_node_1));

    MwsIndexNode* apply_node_1 = new MwsIndexNode();
    apply_node_1->solutions = 1;
    data->children.insert(make_pair(apply4_ni, apply_node_1));

    MwsIndexNode* t_node_1 = new MwsIndexNode();
    t_node_1->solutions = 1;
    data->children.insert(make_pair(t_ni, t_node_1));

    MwsIndexNode* f_node_2 = new MwsIndexNode();
    f_node_2->solutions = 1;
    apply_node_1->children.insert(make_pair(f_ni, f_node_2));

    MwsIndexNode* h_node_3 = new MwsIndexNode();
    h_node_3->solutions = 1;
    f_node_2->children.insert(make_pair(h_ni, h_node_3));

    MwsIndexNode* h_node_4 = new MwsIndexNode();
    h_node_4->solutions = 1;
    h_node_3->children.insert(make_pair(h_ni, h_node_4));

    MwsIndexNode* t_node_5 = new MwsIndexNode();
    t_node_5->solutions = 1;
    h_node_4->children.insert(make_pair(t_ni, t_node_5));

    return data;
}
};

static encoded_formula_t create_test_query() {
    encoded_formula_t result;

    result.data = new encoded_token_t[5];
    result.size = 5;
    result.data[0] = apply4_tok;     // apply, 4
    result.data[1] = f_tok;
    result.data[2] = P_tok;
    result.data[3] = P_tok;
    result.data[4] = t_tok;

    return result;
}

static
result_cb_return_t result_callback(void* handle,
                                   const leaf_t * leaf) {
    UNUSED(handle);
    UNUSED(leaf);

    g_num_hits++;

    return QUERY_CONTINUE;
}

int main() {
    mws::MwsIndexNode* index = Tester::create_test_MwsIndexNode();
    encoded_formula_t query = create_test_query();

    FAIL_ON(query_engine_tester(index, &query, result_callback, NULL)
            == EXIT_FAILURE);
    FAIL_ON(g_num_hits != 1);

    return EXIT_SUCCESS;

fail:
    return EXIT_FAILURE;
}
