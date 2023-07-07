#pragma once

#include "json.h"
#include "map_renderer.h"
#include "serialization.h"
#include "transport_router.h"
#include "transport_catalogue.h"

namespace transport_catalogue {
    namespace detail {
        namespace json {

            class JSONReader {
            public:
                JSONReader() = default;

                JSONReader(Document doc);

                JSONReader(std::istream &input);

                void ParseNodeBase(const Node &root, TransportCatalogue &catalogue);

                void ParseNodeStat(const Node &node, std::vector<StatRequest> &stat_request);

                void ParseNodeRender(const Node &node, map_renderer::RenderSettings &rend_set);

                void ParseNodeRouting(const Node &node, router::RoutingSettings &route_set);

                void ParseNodeSerialization(const Node &node, serialization::SerializationSettings &serialization_set);

                void ParseNodeMakeBase(TransportCatalogue &catalogue,
                                       map_renderer::RenderSettings &render_settings,
                                       router::RoutingSettings &routing_settings,
                                       serialization::SerializationSettings &serialization_settings);

                void ParseNodeProcessRequests(std::vector<StatRequest> &stat_request,
                                              serialization::SerializationSettings &serialization_settings);

                Stop ParseNodeStop(Node &node);

                Bus ParseNodeBus(Node &node, TransportCatalogue &catalogue);

                std::vector<Distance> ParseNodeDistances(Node &node, TransportCatalogue &catalogue);

                const Document &GetDocument() const;

            private:
                Document document_;
            };
        }
    }
}