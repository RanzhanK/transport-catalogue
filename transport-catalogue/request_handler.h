#pragma once

#include "map_renderer.h"
#include "json_builder.h"
#include "transport_router.h"
#include "transport_catalogue.h"

using namespace map_renderer;
using namespace transport_catalogue;
using namespace transport_catalogue::detail::json;
using namespace transport_catalogue::detail::router;
using namespace transport_catalogue::detail::json::builder;

namespace request_handler {

    class RequestHandler {
    public:

        RequestHandler() = default;

        std::optional<RouteInfo> GetRouteInfo(std::string_view start,
                                              std::string_view end,
                                              TransportCatalogue &catalogue,
                                              TransportRouter &routing) const;

        std::vector<geo::Coordinates> GetStopsCoordinates(TransportCatalogue &catalogue_) const;

        std::vector<std::string_view> GetSortBusesNames(TransportCatalogue &catalogue_) const;

        BusQueryResult BusQuery(TransportCatalogue &catalogue, std::string_view bus_name);

        StopQueryResult StopQuery(TransportCatalogue &catalogue, std::string_view stop_name);

        Node ExecuteMakeNodeStop(int id_request, const StopQueryResult &stop_info);

        Node ExecuteMakeNodeBus(int id_request, const BusQueryResult &bus_info);

        Node ExecuteMakeNodeMap(int id_request, TransportCatalogue &catalogue_, RenderSettings render_settings);

        Node ExecuteMakeNodeRoute(StatRequest &request, TransportCatalogue &catalogue, TransportRouter &routing);

        void ExecuteQueries(TransportCatalogue &catalogue,
                            std::vector<StatRequest> &stat_requests,
                            RenderSettings &render_settings,
                            RoutingSettings &routing_settings);

        void ExecuteRenderMap(MapRenderer &map_catalogue, TransportCatalogue &catalogue) const;

        const Document &GetDocument();

    private:
        Document doc_out;
    };
}