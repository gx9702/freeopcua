/// @author Alexander Rykovanov 2012
/// @email rykovanov.as@gmail.com
/// @brief Remote Computer implementaion.
/// @license GNU LGPL
///
/// Distributed under the GNU LGPL License
/// (See accompanying file LICENSE or copy at 
/// http://www.gnu.org/licenses/lgpl.html)
///

#include "uri_facade.h"

#include <opc/ua/protocol/binary/secure_connection.h>
#include <opc/ua/client/computer.h>
#include <opc/ua/client/remote_connection.h>

namespace
{
  using namespace OpcUa;
  using namespace OpcUa::Remote;

  class UaComputer : public OpcUa::Remote::Computer
  {
  public:
    UaComputer(const std::string& uri)
      : ServerUri(uri)
    {
      std::shared_ptr<IOChannel> connection(OpcUa::Connect(ServerUri.Host(), ServerUri.Port()));
      Binary::SecureConnectionParams params;
      params.EndpointUrl = uri;
      params.SecurePolicy = "http://opcfoundation.org/UA/SecurityPolicy#None";
      Channel = OpcUa::Binary::CreateSecureChannel(connection, params);
    }

    virtual void CreateSession(const SessionParameters& parameters)
    {
    }

    virtual void UpdateSession(const IdentifyParameters& parameters)
    {
    }

    virtual void CloseSession()
    {
    }

    virtual std::shared_ptr<EndpointServices> Endpoints() const
    {
      return std::shared_ptr<EndpointServices>();
    }

    virtual std::shared_ptr<ViewServices> Views() const
    {
      return std::shared_ptr<ViewServices>();
    }

    virtual std::shared_ptr<AttributeServices> Attributes() const
    {
      return std::shared_ptr<AttributeServices>();
    }

  private:
    const Uri ServerUri;
    std::shared_ptr<OpcUa::IOChannel> Channel;
  };


}

std::unique_ptr<OpcUa::Remote::Computer> OpcUa::Remote::Connect(const std::string& url)
{
  return std::unique_ptr<OpcUa::Remote::Computer>(new UaComputer(url));
}

