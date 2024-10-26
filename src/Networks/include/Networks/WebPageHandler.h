#pragma once

#include "CivetServer.h"
#include "Noncopyable.h"

#include <string>
#include <map>

namespace Communications
{
    class HttpResponse;

    class WebPageHandler: public Noncopyable, public CivetHandler 
    {
    public:
        WebPageHandler() = default;
        virtual ~WebPageHandler() = default;

        virtual bool Initialize(void* user_data) { return true; };

        bool handleGet(CivetServer *server, struct mg_connection *conn) override;
        
        bool handlePost(CivetServer *server, struct mg_connection *conn) override; 
        

    private:
        bool checkAuth(struct mg_connection* conn);

    protected:
        virtual bool handleGetImpl(HttpResponse* resp, struct mg_connection *conn) { return true; };
        virtual bool handlePostImpl(HttpResponse* resp, struct mg_connection *conn) { return true; };


    protected:
        void ApplyResponse(const HttpResponse& res, struct mg_connection* conn);

    private:

    };
    
    
    
    
} // namespace Communications
