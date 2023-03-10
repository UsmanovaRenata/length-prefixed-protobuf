

#include <iostream>
#include"TestTask.pb.h"
#include<boost/make_shared.hpp>

#if GOOGLE_PROTOBUF_VERSION >= 3012004 
#define PROTOBUF_MESSAGE_BYTE_SIZE(message) ((message).ByteSizeLong()) 
#else 
#define PROTOBUF_MESSAGE_BYTE_SIZE(message) ((message).ByteSize()) 
#endif 

typedef std::vector<char> Data;
typedef boost::shared_ptr<const Data> PointerToConstData;
template <typename Message> 
PointerToConstData serializeDelimited(const Message& msg)
{
    const size_t messageSize = PROTOBUF_MESSAGE_BYTE_SIZE(msg);
    const size_t headerSize = google::protobuf::io::CodedOutputStream::VarintSize32(messageSize);

    const PointerToConstData& result = boost::make_shared<Data>(headerSize + messageSize);
    google::protobuf::uint8* buffer = reinterpret_cast<google::protobuf::uint8*>(*result->begin());

    google::protobuf::io::CodedOutputStream::WriteVarint32ToArray(messageSize, buffer);
    msg.SerializeWithCachedSizesToArray(buffer + headerSize);

    return result;
}

template<typename Message>
std::shared_ptr<Message> parseDelimited(const void* data, size_t size, size_t* bytesConsumed = 0)
{

}

int main()
{
    TestTask::Messages::WrapperMessage Msg;
    TestTask::Messages::FastResponse F;
    std::string *L = new std::string;
    *L = "1234";
    F.set_allocated_current_date_time(L);
    Msg.set_allocated_fast_response(&F);
    std::vector<char> messages;
    messages = *serializeDelimited(Msg);
    delete L;
    return 0;
}
