#pragma once
#include "../CommonDefinitions.h"

template<typename T>
class CNodeGraph
{
public:
    struct SNode
    {
        T m_value;
        std::map<SNode*, unsigned int> m_linkedNodes;

        SNode(T const& value)
            : m_value(value)
        {}

        bool AddLink(SNode* otherNode, unsigned int dist = 1)
        {
            if (m_linkedNodes.find(otherNode) == m_linkedNodes.end())
            {
                m_linkedNodes.insert(std::pair<SNode*, unsigned int>(otherNode, dist));
                return true;
            }
            return false;
        }
    };

    ~CNodeGraph()
    {
        for (std::pair<std::string, SNode*> node : m_nodeMap)
        {
            delete node.second;
        }
    }

    size_t GetNodeCount() const { return m_nodeMap.size(); }
    auto GetBeginIt() { return m_nodeMap.begin(); }
    auto GetEndIt() { return m_nodeMap.end(); }
    SNode* GetNodeFromValue(T const& nodeValue) { return m_nodeMap[nodeValue]; }
    SNode const* GetNodeFromValue(T const& nodeValue) const { return m_nodeMap.find(nodeValue)->second; }

    bool Insert(T const& nodeValue)
    {
        if (m_nodeMap.find(nodeValue) == m_nodeMap.end())
        {
            m_nodeMap.insert(std::pair<T, SNode*>(nodeValue, new SNode(nodeValue)));
            return true;
        }
        return false;
    }

private:
    std::map<T, SNode*> m_nodeMap;
};
