#include "App.h"

Win::App::ThreadPropertyType Win::App::Thread(nullptr, &GetThread_, GetThreadPtr_);

Win::Thread::Object &Win::App::GetThread_(){
	if (Win::App::thread_ == nullptr){
		Win::App::thread_ = std::make_shared<Win::Thread::Object>();
	}

	return *Win::App::thread_;
}

Win::Thread::Object *Win::App::GetThreadPtr_(){
	return &GetThread_();
}

thread_local std::shared_ptr<Win::Thread::Object> Win::App::thread_;
