/**
 * (C) 2017 KISTLER INSTRUMENTE AG, Winterthur, Switzerland
 *
 * @file IConnection.h
 *
 * Created on: Nov 8, 2016
 * Project: sdbus-c++
 * Description: High-level D-Bus IPC C++ library based on sd-bus
 *
 * This file is part of sdbus-c++.
 *
 * sdbus-c++ is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 2.1 of the License, or
 * (at your option) any later version.
 *
 * sdbus-c++ is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with sdbus-c++. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef SDBUS_CXX_ICONNECTION_H_
#define SDBUS_CXX_ICONNECTION_H_

//#include <cstdint>
#include <string>
#include <memory>

namespace sdbus {

    /********************************************//**
     * @class IConnection
     *
     * An interface to D-Bus bus connection. Incorporates implementation
     * of both synchronous and asynchronous processing loop.
     *
     * All methods throw @sdbus::Error in case of failure. The class is
     * thread-aware, but not thread-safe.
     *
     ***********************************************/
    class IConnection
    {
    public:
        /*!
        * @brief Requests D-Bus name on the connection
        *
        * @param[in] name Name to request
        *
        * @throws sdbus::Error in case of failure
        */
        virtual void requestName(const std::string& name) = 0;

        /*!
        * @brief Releases D-Bus name on the connection
        *
        * @param[in] name Name to release
        *
        * @throws sdbus::Error in case of failure
        */
        virtual void releaseName(const std::string& name) = 0;

        /*!
        * @brief Enters the D-Bus processing loop
        *
        * The incoming D-Bus messages are processed in the loop. The method
        * blocks indefinitely, until unblocked via @leaveProcessingLoop.
        *
        * @throws sdbus::Error in case of failure
        */
        virtual void enterProcessingLoop() = 0;

        /*!
        * @brief Enters the D-Bus processing loop in a separate thread
        *
        * The same as @enterProcessingLoop, except that it doesn't block
        * because it runs the loop in a separate thread managed internally.
        */
        virtual void enterProcessingLoopAsync() = 0;

        /*!
        * @brief Leaves the D-Bus processing loop
        *
        * Ends the previously started processing loop.
        *
        * @throws sdbus::Error in case of failure
        */
        virtual void leaveProcessingLoop() = 0;

        inline virtual ~IConnection() = 0;
    };

    IConnection::~IConnection() {}

    /*!
    * @brief Creates/opens D-Bus system connection
    *
    * @return Connection instance
    *
    * @throws sdbus::Error in case of failure
    */
    std::unique_ptr<sdbus::IConnection> createConnection();

    /*!
    * @brief Creates/opens D-Bus system connection with a name
    *
    * @param[in] name Name to request on the connection after its opening
    * @return Connection instance
    *
    * @throws sdbus::Error in case of failure
    */
    std::unique_ptr<sdbus::IConnection> createConnection(const std::string& name);

    /*!
    * @brief Creates/opens D-Bus system connection
    *
    * @return Connection instance
    *
    * @throws sdbus::Error in case of failure
    */
    std::unique_ptr<sdbus::IConnection> createSystemBusConnection();

    /*!
    * @brief Creates/opens D-Bus system connection with a name
    *
    * @param[in] name Name to request on the connection after its opening
    * @return Connection instance
    *
    * @throws sdbus::Error in case of failure
    */
    std::unique_ptr<sdbus::IConnection> createSystemBusConnection(const std::string& name);

    /*!
    * @brief Creates/opens D-Bus session connection
    *
    * @return Connection instance
    *
    * @throws sdbus::Error in case of failure
    */
    std::unique_ptr<sdbus::IConnection> createSessionBusConnection();

    /*!
    * @brief Creates/opens D-Bus session connection with a name
    *
    * @param[in] name Name to request on the connection after its opening
    * @return Connection instance
    *
    * @throws sdbus::Error in case of failure
    */
    std::unique_ptr<sdbus::IConnection> createSessionBusConnection(const std::string& name);

}

#endif /* SDBUS_CXX_ICONNECTION_H_ */
