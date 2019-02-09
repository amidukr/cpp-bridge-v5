#include<gtest/gtest.h>
#include<myholderclass.hpp>

TEST(mygenericclass_test, mygenericclass_recursive_test)
{
	MyHolderClass my_holder_class;
	
	ASSERT_STREQ("MyHoldVariable of MyHolderClass", my_holder_class.GetHoldVariable());
}
