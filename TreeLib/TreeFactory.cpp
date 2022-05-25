/**
 * \file TreeFactory.cpp
 *
 * \author Charles Owen
 *
 * You are allowed to change this file.
 */

#include "pch.h"
#include "TreeFactory.h"
#include "Tree.h"
#include "Basket.h"
#include "FunctionalTree.h"
#include "FunctionalBasket.h"
#include "TreeSeedDlg.h"

using namespace std;

/**
 * Constructor
 */
CTreeFactory::CTreeFactory()
{
}


/**
 * Destructor
 */
CTreeFactory::~CTreeFactory()
{
}


/**
 * Create a Tree object
 * \returns Object of type CTree
 */
std::shared_ptr<CTree> CTreeFactory::CreateTree()
{
	// Creates the tree object
	shared_ptr<CTree> tree = make_shared<CFunctionalTree>();

	return tree;
}


/**
 * Create a Basket object
 * \returns Object of type CBasket
 */
std::shared_ptr<CBasket> CTreeFactory::CreateBasket()
{
	// Creates the basket object
	shared_ptr<CBasket> basket = make_shared<CFunctionalBasket>();

	return basket;
}

