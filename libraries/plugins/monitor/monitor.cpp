/*
 * Copyright (c) 2018 Wang Tao (hutaow@hotmail.com), and contributors.
 *
 * The MIT License
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#include <graphene/monitor/monitor.hpp>

#include <graphene/chain/database.hpp>

#include <fc/io/fstream.hpp>

using namespace graphene::monitor_plugin;
namespace bpo = boost::program_options;
using std::string;

#define MONITOR_OPT_ACTION_TYPE "monitor-action-type"

void monitor_plugin::plugin_set_program_options(
   boost::program_options::options_description& command_line_options,
   boost::program_options::options_description& config_file_options)
{
   command_line_options.add_options()
         (MONITOR_OPT_ACTION_TYPE, bpo::value<uint32_t>(), "The type of operation monitored")
         ;
   config_file_options.add(command_line_options);
}

std::string monitor_plugin::plugin_name()const
{
    return "monitor";
}

std::string monitor_plugin::plugin_description()const
{
    return "Monitor transaction status.";
}

void monitor_plugin::plugin_initialize(const boost::program_options::variables_map& options) {
    try {
        ilog("monitor plugin: plugin_initialize() begin");
        
        if (options.count(MONITOR_OPT_ACTION_TYPE)) {
            monitor_action_type = options[MONITOR_OPT_ACTION_TYPE].as<uint32_t>();
        } else {
            monitor_action_type = MONITOR_ACTION_TYPE_ALL;
        }

        database().applied_block.connect( [&]( const graphene::chain::signed_block& blk ) {
            monitor_signed_block( blk );
        });

        ilog("monitor plugin: plugin_initialize() end");
    } FC_LOG_AND_RETHROW()

    return;
}

void monitor_plugin::plugin_startup() {
    return;
}

void monitor_plugin::plugin_shutdown() {
    return;
}

void monitor_plugin::monitor_signed_block(const graphene::chain::signed_block& blk) {
    for (int i = 0; i < blk.transactions.size(); ++i) {
        chain::processed_transaction trans = blk.transactions[i];
        string act_str = trans.id().str();
        printf(">>> action: %s \r\n", act_str.c_str());
    }
    return;
}
