<?php

namespace SmashcastApi;

use GuzzleHttp\Client;

class SmashcastGuzzleClient extends Client
{
    private const BASE_URI = 'https://api.smashcast.tv/';

    public function __construct(array $config = [])
    {
        parent::__construct($config + [
                'base_uri' => self::BASE_URI,
                'timeout' => 30,
                'headers' => ['Content-Type' => 'application/json'],
            ]);
    }
}
