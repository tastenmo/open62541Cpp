#ifndef CLIENTBROWSER_H
#define CLIENTBROWSER_H
#include <open62541client.h>
namespace Open62541
{

/*!
      \brief The ClientBrowser class
*/
class ClientBrowser {
        Client &_client;
        // browser call back
        std::vector<BrowseItem> _list;
        //
        static UA_StatusCode browseIter(UA_NodeId childId, UA_Boolean isInverse, UA_NodeId referenceTypeId, void *handle);
        //
    public:
        /*!
            \brief ClientBrowser
            \param c
        */
        ClientBrowser(Client &c) : _client(c) {}
        /*!
            \brief ~ClientBrowser
        */
        virtual ~ClientBrowser() {}
        /*!
            \brief browse
            \param start
        */
        void browse(UA_NodeId start) {
            _list.clear();
            UA_Client_forEachChildNodeCall(_client.client(), start, browseIter, (void *) this);
        }
        /*!
            \brief process
            \param childId
            \param referenceTypeId
        */
        virtual void process(UA_NodeId childId,  UA_NodeId referenceTypeId) {
            std::string s;
            int i;
            NodeId n;
            n = childId;
            if (_client.browseName(n, s, i)) {
                _list.push_back(BrowseItem(s, i, childId, referenceTypeId));
            }
        }
        /*!
            \brief list
            \return
        */
        std::vector<BrowseItem> &list() {
            return _list;
        }
        /*!
            \brief print
            \param os
        */
        void print(std::ostream &os) {
            for (BrowseItem &i : _list) {
                std::string s;
                int j;
                NodeId n;
                n = i.childId;
                if (_client.browseName(n, s, j)) {
                    os << toString(i.childId) << " ns:" << i.nameSpace
                       << ": "  << i.name  << " Ref:"
                       << toString(i.referenceTypeId) << std::endl;
                }
            }
        }
        /*!
            \brief find
            \param s
            \return
        */
        int find(const std::string &s) {
            int ret = -1;
            for (int i = 0; i < int(_list.size()); i++) {
                BrowseItem &b = _list[i];
                if (b.name == s) return i;
            }
            return ret;
        }


};

}
#endif // CLIENTBROWSER_H