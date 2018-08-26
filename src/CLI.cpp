/*
 * CLI.cpp
 *
 *  Created on: Aug-11-2018
 *      Author: Aakash Sahai
 */

#include "CLI.h"

namespace mksgen {

CLI::Registry CLI::_registry[10];
CLI::Object CLI::_objects[10];
CLI::Command CLI::_cmd;
char CLI::_buf[CMD_BUF_SIZE+1];
char *CLI::_bp = CLI::_buf;
int CLI::_buflen = 0;
Task *CLI::_task;


CLI::CLI() {
}

CLI::~CLI() {
}

void CLI::begin(Scheduler &runner) {
  _task = new Task(1000, TASK_FOREVER, _run, &runner);
  _task->enable();
}

void CLI::_parse(void) {
	_cmd.cmd = _buf;
	char *ptr = _buf;
	_cmd.nargs = 0;
	while ((ptr = strchr(ptr, ' ')) && _cmd.nargs < MAX_ARGS) {
		*ptr = 0;
		_cmd.args[_cmd.nargs] = ++ptr;
		_cmd.nargs++;
	}
	Serial.print("Command: ");
	Serial.print(_cmd.cmd);
	for (int i = 0; i < _cmd.nargs; i++) {
		Serial.print(':');
		Serial.print(_cmd.args[i]);
	}
	Serial.println('.');
	_execute();
}

void CLI::_execute(void) {
	if (strcmp("begin", _cmd.cmd) == 0) {
		Serial.println("begin ok");
	} else if (strcmp("create", _cmd.cmd) == 0) {
		Serial.println("create ok");
	} else if (strcmp("do", _cmd.cmd) == 0) {
		Serial.println("do ok");
	} else if (strcmp("wait", _cmd.cmd) == 0) {
		Serial.println("wait ok");
	} else if (strcmp("get", _cmd.cmd) == 0) {
		Serial.println("get ok");
	} else if (strcmp("end", _cmd.cmd) == 0) {
		Serial.println("end ok");
	} else {
		Serial.print("ko ");
		Serial.println(_cmd.cmd);
	}
}

void CLI::_run(void) {
	size_t bytes;
	bool doParse = 0;

	if ((bytes = Serial.available()) <= 0)
		return;

	bytes = Serial.readBytes(_bp, min(bytes, (CMD_BUF_SIZE - _buflen)));
	for (int i= 0; i < bytes; i++) {
		if (_bp[i] == '\n') {
			_bp[i] = 0;
			doParse = 1;
		}
	}
	_buflen += bytes;
	_bp += bytes;
	if (doParse || (_buflen == CMD_BUF_SIZE)) {
  	_parse();
		_bp = _buf;
		_buflen = 0;
	}
}

}
