#include "net.hpp"

namespace net {

addr::addr(short int port)
{
	m_addr = {0};
	m_addr.sin_family = AF_INET;
	m_addr.sin_addr.s_addr = INADDR_ANY;
	m_addr.sin_port = port;
}

sockaddr * addr::as_sockaddr()
{
	return reinterpret_cast<sockaddr*>(&m_addr);
}

sockaddr const * addr::as_sockaddr() const
{
	return reinterpret_cast<sockaddr const*>(&m_addr);
}

socklen_t * addr::len()
{
	return &m_sl;
}
socklen_t const* addr::len() const
{
	return &m_sl;
}

socket::socket(int fd) : m_fd(fd) {}

socket::socket()
{
	m_fd = ::socket(PF_INET, SOCK_STREAM, 0);
}

socket::~socket()
{
	if (m_fd != -1)
		close(m_fd);
}

socket::socket(socket &&s) : m_fd(s.m_fd)
{
	s.m_fd = -1;
}

void socket::bind(addr const& a)
{
	::bind(m_fd, a.as_sockaddr(), *a.len());
}

void socket::listen(int n)
{
	::listen(m_fd, n);
}

void socket::connect(addr const &a)
{
	::connect(m_fd, a.as_sockaddr(), *a.len());
}

socket socket::accept()
{
	int fd = ::accept(m_fd, nullptr, nullptr);
	return fd;
}

}