#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

namespace net {

class addr
{
private:
	sockaddr_in m_addr;
	socklen_t m_sl;

public:
	addr(short int port);
	sockaddr *as_sockaddr();
	sockaddr const *as_sockaddr() const;
	socklen_t *len();
	socklen_t const* len() const;
};

class socket
{
private:
	int m_fd;

	socket(int fd);

public:
	socket();
	~socket();
	socket(socket &&s);
	
	void bind(addr const &a);
	void listen(int n);
	void connect(addr const &a);
	socket accept();

	void send();
	void recv();
};

}