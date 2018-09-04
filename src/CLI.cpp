/*
 * CLI.cpp
 *
 *  Created on: Aug-11-2018
 *      Author: Aakash Sahai
 */

#include "CLI.h"

namespace mksgen {

CLI::Registry CLI::_registry[];
CLI::Object CLI::_objects[];
CLI::Command CLI::_cmd;
char CLI::_buf[CMD_BUF_SIZE+1];
char *CLI::_bp = CLI::_buf;
int CLI::_buflen = 0;
int CLI::_objectQty = 0;
int CLI::_moduleQty = 0;
Scheduler *CLI::_sched = 0;
Task *CLI::_task;


CLI::CLI() {
}

CLI::~CLI() {
}

void CLI::begin(Scheduler &runner) {
  _task = new Task(1000, TASK_FOREVER, _run, &runner);
  _sched = &runner;
  _task->enable();
}

void CLI::addModule(const char *module, CreateFn create) {
  if (_moduleQty == MAX_MODULES) {
    Serial.println("max modules already registered");
    return;
  }
  strncpy(_registry[_moduleQty].name, module, MAX_MODULE_NAME_SIZE);
  _registry[_moduleQty].create = create;
  _moduleQty++;
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
  /*
	Serial.print("Command: ");
	Serial.print(_cmd.cmd);
	for (int i = 0; i < _cmd.nargs; i++) {
		Serial.print(':');
		Serial.print(_cmd.args[i]);
	}
	Serial.println('.');
  */
	_execute();
}

const char *CLI::_create(void) {
  int i;

  if (_objectQty == MAX_OBJECTS) {
    return "max objects already exist";
  }
  strncpy(_objects[_objectQty].name, _cmd.args[0], MAX_NAME_SIZE);
  for (i = 0; i < _moduleQty; i++) {
    if (strcmp(_registry[i].name, _cmd.args[2]) == 0) {
      break;
    }
  }
  if (i == MAX_MODULES) {
    return "no such class";
  }
  _objects[_objectQty].obj = _registry[i].create(&_cmd.args[3]);
  _objects[_objectQty].obj->begin(*_sched);
  _objectQty++;
  return 0;
}

Runnable *CLI::_findObject(const char *name) {
  int i;

  for (i = 0; i < _objectQty; i++) {
    if (strcmp(_objects[i].name, name) == 0) {
      return _objects[i].obj;
    }
  }
  return 0;
}

void CLI::_execute(void) {
  Runnable *obj = _findObject(_cmd.args[0]);
  if (strcmp("create", _cmd.cmd) == 0) {
    if (obj != 0) {
      Serial.println("create failed: object already exists");
      return;
    }
    const char *err = CLI::_create();
    if (err) {
      Serial.print("create failed: ");
      Serial.println(err);
    } else {
      Serial.println("create ok");
    }
    return;
	}

  if (obj == 0) {
    return;
  }

  if (strcmp("do", _cmd.cmd) == 0) {
		Serial.println("do ok");
	} else if (strcmp("get", _cmd.cmd) == 0) {
    char *result;
    obj->get(&_cmd.args[1], &result);
    if (result) Serial.println(result);
	} else if (strcmp("set", _cmd.cmd) == 0) {
    char *result;
		obj->set(&_cmd.args[1], &result);
    Serial.println(result);
	} else {
		Serial.print("Unknown command: ");
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
