#pragma once
#include "QueueArray.h"
#include <iostream>

class WrongQueueSize
{
public:
	static void QueueFlowTest()
	{

            QueueArray<int>& queue = *new QueueArray<int>(); // std size - 128

            try
            {
                for (int i = 1; i < 150; i++)
                {
                    queue.enQueue(i);
                }
            }
            catch (const std::exception& e)
            {
                std::cout << e.what();
            }

            std::cout << std::endl;

            try
            {
                for (size_t i = 1; i < 150; i++)
                {
                    queue.deQueue();
                }
            }
            catch (const std::exception& e)
            {
                std::cout << e.what();
            }

            std::cout << std::endl;

	}
};