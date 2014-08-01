/*
 * cxmpies.h
 *
 *  Created on: 12.01.2014
 *      Author: andreas
 */

#ifndef CXMPIES_H_
#define CXMPIES_H_

#ifdef __cplusplus
extern "C" {
#endif
#include <inttypes.h>
#ifdef __cplusplus
}
#endif

#include <map>

#include "cxmpie.h"
#include "cxmpie_command.h"
#include "cxmpie_name.h"
#include "cxmpie_portinfo.h"
#include "cxmpie_dpid.h"
#include "cxmpie_multipart.h"
#include "xdpd_mgmt_protocol.h"
#include "rofl/common/croflexception.h"

namespace xdpd {
namespace mgmt {
namespace protocol {

class eXmpIEsBase			: public rofl::RoflException {};
class eXmpIEsInval			: public eXmpIEsBase {};
class eXmpIEsNotFound		: public eXmpIEsBase {};

class cxmpies
{
	std::map<uint16_t, cxmpie*>		xmpmap;

public: // iterators

	typedef typename std::map<uint16_t, cxmpie*>::iterator iterator;
	typedef typename std::map<uint16_t, cxmpie*>::const_iterator const_iterator;
	iterator begin() { return xmpmap.begin(); }
	iterator end() { return xmpmap.end(); }
	const_iterator begin() const { return xmpmap.begin(); }
	const_iterator end() const { return xmpmap.end(); }

	typedef typename std::map<uint16_t, cxmpie*>::reverse_iterator reverse_iterator;
	typedef typename std::map<uint16_t, cxmpie*>::const_reverse_iterator const_reverse_iterator;
	reverse_iterator rbegin() { return xmpmap.rbegin(); }
	reverse_iterator rend() { return xmpmap.rend(); }

public:

	/**
	 *
	 */
	cxmpies();

	/**
	 *
	 */
	cxmpies(
			uint8_t* buf, size_t buflen);

	/**
	 *
	 */
	cxmpies(
			cxmpies const& xmpies);

	/**
	 *
	 */
	cxmpies&
	operator= (
			cxmpies const& xmpies);

	/**
	 *
	 */
	virtual
	~cxmpies();

public:

	/**
	 *
	 */
	void
	clear();

	/**
	 *
	 */
	size_t
	size() const { return xmpmap.size(); };

	/**
	 *
	 */
	virtual size_t
	length() const;

	/**
	 *
	 */
	virtual void
	pack(
			uint8_t* buf, size_t buflen);

	/**
	 *
	 */
	virtual void
	unpack(
			uint8_t* buf, size_t buflen);

public:

	/*
	 * information element: command
	 */

	cxmpie_command&
	add_ie_command();

	cxmpie_command&
	set_ie_command();

	cxmpie_command const&
	get_ie_command() const;

	void
	drop_ie_command();

	bool
	has_ie_command() const;

	/*
	 * information element: portname
	 */

	cxmpie_name&
	add_ie_portname();

	cxmpie_name&
	set_ie_portname();

	cxmpie_name const&
	get_ie_portname() const;

	void
	drop_ie_portname();

	bool
	has_ie_portname() const;

	/*
	 * information element: portinfo
	 */

	cxmpie_portinfo&
	add_ie_portinfo();

	cxmpie_portinfo&
	set_ie_portinfo();

	cxmpie_portinfo const&
	get_ie_portinfo() const;

	void
	drop_ie_portinfo();

	bool
	has_ie_portinfo() const;

	/*
	 * information element: dpid
	 */

	cxmpie_dpid&
	add_ie_dpid();

	cxmpie_dpid&
	set_ie_dpid();

	cxmpie_dpid const&
	get_ie_dpid() const;

	void
	drop_ie_dpid();

	bool
	has_ie_dpid() const;

	/*
	 * information element: lsiname
	 */

	cxmpie_name&
	add_ie_lsiname();

	cxmpie_name&
	set_ie_lsiname();

	cxmpie_name const&
	get_ie_lsiname() const;

	void
	drop_ie_lsiname();

	bool
	has_ie_lsiname() const;

	/*
	 * information element: multipart
	 */
	cxmpie_multipart&
	add_ie_multipart();

	cxmpie_multipart&
	set_ie_multipart();

	cxmpie_multipart const&
	get_ie_multipart() const;

	void
	drop_ie_multipart();

	bool
	has_ie_multipart() const;

private:

	/**
	 *
	 */
	void
	map_and_insert(
			cxmpie const& xmpie);

public:

	friend std::ostream&
	operator<< (std::ostream& os, cxmpies const& xmpies) {
		os << rofl::indent(0) << "<cxmpies #IEs:" << xmpies.size() << " >" << std::endl;
		rofl::indent i(2);
		for (cxmpies::const_iterator
				it = xmpies.begin(); it != xmpies.end(); ++it) {
			switch (it->second->get_type()) {
			case XMPIET_NONE: {
				os << "  " << *(it->second);
			} break;
			case XMPIET_COMMAND: {
				os << "  " << dynamic_cast<cxmpie_command const&>( *(it->second) );
			} break;
			case XMPIET_LSINAME:
			case XMPIET_PORTNAME: {
				os << "  " << dynamic_cast<cxmpie_name const&>( *(it->second) );
			} break;
			case XMPIET_PORTINFO: {
				os << "  " << dynamic_cast<cxmpie_portinfo const&>( *(it->second) );
			} break;
			case XMPIET_DPID: {
				os << "  " << dynamic_cast<cxmpie_dpid const&>( *(it->second) );
			} break;
			case XMPIET_MULTIPART: {
				os << "  " << dynamic_cast<cxmpie_multipart const&>( *(it->second) );
			} break;
			default: {
				os << "  " << *(it->second);
			};
			}
		}
		return os;
	};
};

}; // end of namespace protocol
}; // end of namespace mgmt
}; // end of namespace xdpd

#endif /* CXMPIES_H_ */
