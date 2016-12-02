<?php
/**
 * PHP version 5 ou plus
 *
 * @category   L3 Web Persistance
 * @package    web.tp3
 * @author     Isabelle Mirbel <Isabelle.Mirbel@unice.fr>
 * @version    1.0
 * @link       http://www-mips.unice.fr/~ai401938/web/tp3
 */

function __autoload($classname)
{
	include_once "$classname.inc";
}
?>