<?php

declare(strict_types=1);

namespace SmashcastApi\Api;

use GuzzleHttp\Client;
use GuzzleHttp\Exception\GuzzleException;
use GuzzleHttp\Psr7\Request;
use GuzzleHttp\RequestOptions;
use Psr\Http\Message\ResponseInterface;

abstract class AbstractApiBase
{
    protected $appName;
    protected $appToken;
    protected $guzzleClient;

    public function __construct(string $appName, string $appToken, Client $guzzleApp)
    {
        $this->appName = $appName;
        $this->appToken = $appToken;
        $this->guzzleClient = $guzzleApp;
    }

    /**
     * @throws GuzzleException
     */
    protected function apiGet(string $uriEndpoint, array $queryParams = [], string $accessToken = null): ResponseInterface
    {
        if ($accessToken)
            $queryParams['authToken'] = $accessToken;

        $request = new Request(
            'GET',
            sprintf('%s%s', $uriEndpoint, $this->generateQueryParams($queryParams))
        );

        return $this->guzzleClient->send($request);
    }

    /**
     * @throws GuzzleException
     */
    protected function apiPost(string $uriEndpoint, ?array $body = null, string $authToken = null): ResponseInterface
    {
        if ($authToken)
            $body['authToken'] = $authToken;

        $request = new Request(
            'POST',
            $uriEndpoint);

        $options = $body
            ? [
                RequestOptions::JSON => $body
            ]
            : [];

        return $this->guzzleClient->send($request, $options);
    }

    /**
     * $queryParamsMap should be a mapping of the param key expected in the API call URL,
     * and the value to be sent for that key.
     *
     * ['param_key' => 42, 'other_key' => 'asdf']
     * would result in
     * ?param_key=42&other_key=asdf
     */
    protected function generateQueryParams(array $queryParams): string
    {
        $queryStringParams = '';
        foreach ($queryParams as $key => $value) {
            if ($value) {
                $format = is_int($value) ? '%d' : '%s';
                $queryStringParams .= sprintf('&%s=' . $format, $key, $value);
            }
        }

        return $queryStringParams ? '?' . substr($queryStringParams, 1) : '';
    }
}
