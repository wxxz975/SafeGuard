#pragma once
#include <unordered_map>
#include <any>
#include <stdexcept>

#define SGSERVICE(Type) Common::ServiceLocator::Get<Type>();

namespace Common
{
    // from: overload 
    class ServiceLocator
	{
	public:
		/**
		* Register a service in the service locator
		* @param p_service
		*/
		template<typename T>
		static void Provide(T& p_service)
		{
			__SERVICES[typeid(T).hash_code()] = std::any(&p_service);
		}
		
		/**
		* Returns a service of the given type (Make sure that your provided the service before calling this method)
		*/
		template<typename T>
		static T& Get()
		{
			auto service = std::any_cast<T*>(__SERVICES[typeid(T).hash_code()]);
			if (!service) {
				throw std::runtime_error("Service pointer is null.");
			}
			return *service;
		}

		template<typename T>
		static bool IsValid(){
			return __SERVICES.count(typeid(T).hash_code());
		}

	private:
		static std::unordered_map<size_t, std::any> __SERVICES;
	};
    
} // namespace ServiceLocator
