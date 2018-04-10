// strand_test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>

#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/lockfree/stack.hpp>
#include <boost/asio/strand.hpp>

using boost::asio::ip::udp;
//using namespace boost;
//using namespace asio;

boost::asio::io_service m_service;
boost::asio::io_context::strand m_strand(m_service);


//timer1_.async_wait(boost::asio::bind_executor(strand_,
//	boost::bind(&printer::print1, this)));

void func1()
{
	static int i = 0;
	::printf("aaaaaaaaaaaaaaaaaaaaa\n");// , i); i++;
	//::printf("%d\n",++i);// , i); i++;
	::printf("bbbbbbbbbbbbbbbbbbbbb\n");
	m_strand.post(boost::bind(&func1));
}

void func2()
{
	static int i = 0;
	::printf("1111111111111111111111111\n");// , i); i++;
										//::printf("%d\n",++i);// , i); i++;
	::printf("2222222222222222222222222\n");
	m_service.post(boost::bind(&func2));
}

void entry1()
{
	m_strand.post(boost::bind(&func1));
	m_service.run();
}

void entry2()
{
	m_service.post(boost::bind(&func2));
	m_service.run();
}

int main()
{
	boost::thread_group group;
//	udp::socket socket_(m_service, udp::endpoint(udp::v4(), 14));
//	boost::asio::io_context io_context_;
//	//udp::socket socket_;
//	udp::endpoint remote_endpoint_;
//	udp::endpoint tar_upper_endpoint_;
//	udp::endpoint tar_device_endpoint_;
////	boost::thread_group group;
//	char send_buffer_[256];
//	char recv_buffer_[256];
//	socket_.async_receive_from(
//		boost::asio::buffer(recv_buffer_), remote_endpoint_,
//		boost::bind(boost::asio::bind_executor(m_strand, boost::bind(&func1)),
//			boost::asio::placeholders::error,
//			boost::asio::placeholders::bytes_transferred));


	for (int i = 0; i < 4; i++)
	{
		if (i < 2)
		{
			group.create_thread(
				//boost::asio::bind_executor( m_strand, boost::bind(&func1))
				entry1
			);
		}
		else
		{
			group.create_thread(
				//boost::asio::bind_executor( m_strand, boost::bind(&func1))
				entry2
			);
		}
	}
	
	group.join_all();

	return 0;
}




//namespace
//{
//	// strand提供串行执行, 能够保证线程安全, 同时被post或dispatch的方法, 不会被并发的执行.   
//	// io_service不能保证线程安全  
//	boost::asio::io_service m_service;
//	boost::asio::io_context::strand m_strand(m_service);
//	boost::mutex m_mutex;
//
//	void print(int id)
//	{
//		// boost::mutex::scoped_lock lock(m_mutex);  
//		static int count = 0;
//		//PRINT_DEBUG("id: " << boost::lexical_cast<std::string>(id));
//		//PRINT_DEBUG("count: " << boost::lexical_cast<std::string>(++count));
//		::printf("id: %d\n",id);
//		::printf("count: %d\n", ++count);
//	}
//
//	void ioRun1()
//	{
//		while (true)
//		{
//			m_service.run();
//		}
//	}
//
//	void ioRun2()
//	{
//		while (true)
//		{
//			m_service.run();
//		}
//	}
//
//	void strand_print1()
//	{
//		// PRINT_DEBUG("Enter print1");  
//		m_strand.dispatch(boost::bind(print, 1));
//		// PRINT_DEBUG("Exit print1");  
//	}
//
//	void strand_print2()
//	{
//		// PRINT_DEBUG("Enter print2");  
//		m_strand.post(boost::bind(print, 2));
//		// PRINT_DEBUG("Exit print2");  
//	}
//
//	void strand_print3()
//	{
//		// PRINT_DEBUG("Enter print3");                
//		m_strand.post(boost::bind(print, 3));
//		// PRINT_DEBUG("Exit print3");  
//	}
//
//	void strand_print4()
//	{
//		// PRINT_DEBUG("Enter print4");  
//		m_strand.post(boost::bind(print, 4));
//		// PRINT_DEBUG("Exit print4");  
//	}
//
//	// 将上面的m_strand换成m_service后，  
//	void service_print1()
//	{
//		// PRINT_DEBUG("Enter print1");  
//		m_service.dispatch(boost::bind(print, 1));
//		// PRINT_DEBUG("Exit print1");  
//	}
//
//	void service_print2()
//	{
//		// PRINT_DEBUG("Enter print2");  
//		m_service.post(boost::bind(print, 2));
//		// PRINT_DEBUG("Exit print2");  
//	}
//
//	void service_print3()
//	{
//		// PRINT_DEBUG("Enter print3");                
//		m_service.post(boost::bind(print, 3));
//		// PRINT_DEBUG("Exit print3");  
//	}
//
//	void service_print4()
//	{
//		// PRINT_DEBUG("Enter print4");  
//		m_service.post(boost::bind(print, 4));
//		// PRINT_DEBUG("Exit print4");  
//	}
//}
//
//void test_strand()
//{
//	boost::thread ios1(ioRun1);
//	boost::thread ios2(ioRun2);
//
//	boost::thread t1(strand_print1);
//	boost::thread t2(strand_print2);
//	boost::thread t3(strand_print3);
//	boost::thread t4(strand_print4);
//
//	t1.join();
//	t2.join();
//	t3.join();
//	t4.join();
//
//	m_service.run();
//}
//
//void test_service()
//{
//	boost::thread ios1(ioRun1);
//	boost::thread ios2(ioRun2);
//
//	boost::thread t1(service_print1);
//	boost::thread t2(service_print2);
//	boost::thread t3(service_print3);
//	boost::thread t4(service_print4);
//
//	t1.join();
//	t2.join();
//	t3.join();
//	t4.join();
//
//	m_service.run();
//}
//
//void main()
//{
//	//test_service();
//	test_strand();
//}
