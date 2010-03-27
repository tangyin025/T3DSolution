
#ifndef __MYSINGLETON_H__
#define __MYSINGLETON_H__

#include <boost/shared_ptr.hpp>

namespace my
{
	template <class DRIVED_CLASS>
	class Singleton
	{
	protected:
		typedef boost::shared_ptr<DRIVED_CLASS> DRIVED_CLASS_PTR;

		static DRIVED_CLASS_PTR s_ptr;

	public:
		Singleton(void)
		{
			_ASSERT(NULL == s_ptr);
		}

		~Singleton(void)
		{
			_ASSERT(this == s_ptr.get());
		}

	public:
		static DRIVED_CLASS * getSingletonPtr(void)
		{
			if(NULL == s_ptr)
			{
				s_ptr = DRIVED_CLASS_PTR(new DRIVED_CLASS());
			}

			return s_ptr.get();
		}

		static DRIVED_CLASS & getSingleton(void)
		{
			return * getSingletonPtr();
		}
	};
}

#endif // __MYSINGLETON_H__
