<?php

// autoload_static.php @generated by Composer

namespace Composer\Autoload;

class ComposerStaticInit032cfc9a1921a8d0b0a2f3c64fd1a982
{
    public static $files = array (
        '7b11c4dc42b3b3023073cb14e519683c' => __DIR__ . '/..' . '/ralouphie/getallheaders/src/getallheaders.php',
        'c964ee0ededf28c96ebd9db5099ef910' => __DIR__ . '/..' . '/guzzlehttp/promises/src/functions_include.php',
        'a0edc8309cc5e1d60e3047b5df6b7052' => __DIR__ . '/..' . '/guzzlehttp/psr7/src/functions_include.php',
        '37a3dc5111fe8f707ab4c132ef1dbc62' => __DIR__ . '/..' . '/guzzlehttp/guzzle/src/functions_include.php',
    );

    public static $prefixLengthsPsr4 = array (
        'P' => 
        array (
            'Psr\\Http\\Message\\' => 17,
        ),
        'I' => 
        array (
            'InfluxDB\\' => 9,
        ),
        'G' => 
        array (
            'GuzzleHttp\\Psr7\\' => 16,
            'GuzzleHttp\\Promise\\' => 19,
            'GuzzleHttp\\' => 11,
        ),
    );

    public static $prefixDirsPsr4 = array (
        'Psr\\Http\\Message\\' => 
        array (
            0 => __DIR__ . '/..' . '/psr/http-message/src',
        ),
        'InfluxDB\\' => 
        array (
            0 => __DIR__ . '/..' . '/influxdb/influxdb-php/src/InfluxDB',
        ),
        'GuzzleHttp\\Psr7\\' => 
        array (
            0 => __DIR__ . '/..' . '/guzzlehttp/psr7/src',
        ),
        'GuzzleHttp\\Promise\\' => 
        array (
            0 => __DIR__ . '/..' . '/guzzlehttp/promises/src',
        ),
        'GuzzleHttp\\' => 
        array (
            0 => __DIR__ . '/..' . '/guzzlehttp/guzzle/src',
        ),
    );

    public static $classMap = array (
        'crodas\\InfluxPHP\\BaseHTTP' => __DIR__ . '/..' . '/crodas/influx-php/lib/InfluxPHP/BaseHTTP.php',
        'crodas\\InfluxPHP\\Client' => __DIR__ . '/..' . '/crodas/influx-php/lib/InfluxPHP/Client.php',
        'crodas\\InfluxPHP\\DB' => __DIR__ . '/..' . '/crodas/influx-php/lib/InfluxPHP/DB.php',
        'crodas\\InfluxPHP\\MultipleResultSeriesObject' => __DIR__ . '/..' . '/crodas/influx-php/lib/InfluxPHP/MultipleResultSeriesObject.php',
        'crodas\\InfluxPHP\\ResultSeriesObject' => __DIR__ . '/..' . '/crodas/influx-php/lib/InfluxPHP/ResultSeriesObject.php',
        'crodas\\InfluxPHP\\ResultsetBuilder' => __DIR__ . '/..' . '/crodas/influx-php/lib/InfluxPHP/ResultsetBuilder.php',
    );

    public static function getInitializer(ClassLoader $loader)
    {
        return \Closure::bind(function () use ($loader) {
            $loader->prefixLengthsPsr4 = ComposerStaticInit032cfc9a1921a8d0b0a2f3c64fd1a982::$prefixLengthsPsr4;
            $loader->prefixDirsPsr4 = ComposerStaticInit032cfc9a1921a8d0b0a2f3c64fd1a982::$prefixDirsPsr4;
            $loader->classMap = ComposerStaticInit032cfc9a1921a8d0b0a2f3c64fd1a982::$classMap;

        }, null, ClassLoader::class);
    }
}
