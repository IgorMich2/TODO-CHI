#pragma once
#include <string>
#include <chrono>
#include "todo.h"
#include <stdio.h>
#include <chrono>
#include <thread>
#include <functional>
#include <iostream>

namespace list {
	struct TodoItem {
		std::chrono::time_point<std::chrono::system_clock> triggerTime;
		std::string message;
	};
}