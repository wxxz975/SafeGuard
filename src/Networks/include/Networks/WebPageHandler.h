#pragma once

#include <string>
#include <map>


#include "civetweb/CivetServer.h"


namespace Networks
{
    class HttpResponse;

    class WebPageHandler: public CivetHandler 
    {
    public:
        WebPageHandler() = default;
        virtual ~WebPageHandler() = default;

        virtual bool Initialize(void* user_data) { return true; };

    public:
        
        virtual bool handleGet(CivetServer *server, struct mg_connection *conn) override;
        
        virtual bool handlePost(CivetServer *server, struct mg_connection *conn) override; 
        

    private:
        bool CheckAuth(struct mg_connection* conn);

    protected:
        virtual bool HandleGetImpl(HttpResponse* resp, struct mg_connection *conn) { return true; };
        virtual bool HandlePostImpl(HttpResponse* resp, struct mg_connection *conn) { return true; };


    protected:
        void ApplyResponse(const HttpResponse& res, struct mg_connection* conn);

    
    };
    
    
    
    
} // namespace Networks
